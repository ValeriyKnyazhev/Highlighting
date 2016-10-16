#include "stdafx.h"
#pragma comment(lib, "comctl32.lib")

#include "YaPyN_Editor.h"

const wchar_t* textForExit = L"Завершение работы";
const wchar_t* textForNewFile = L"Действие со старым файлом";

const wchar_t* resultText = L"Result";

const int YaPyN_Editor::sizeBetweenCells = 10;
const int YaPyN_Editor::marginLeftRightCells = 10;
const int maxSizeForFileName = 64;

const char cellBeginSymbol = '{';
const char cellEndSymbol = '}';

const COLORREF colorActiveCell = RGB( 200, 200, 200 );

YaPyN_Editor::YaPyN_Editor()
{
	handleMainWindow = 0;
	handleToolbar = 0;
	changed = false;
	childrensWindow.resize( 0 );
	activeCell = childrensWindow.end();
	buttonsBitmaps.clear();
}

bool YaPyN_Editor::RegisterClass()
{
	WNDCLASSEX windowClass;
	::ZeroMemory( &windowClass, sizeof( windowClass ) );
	windowClass.cbSize = sizeof( WNDCLASSEX );
	windowClass.lpfnWndProc = YaPyN_Editor::windowProc;
	windowClass.hInstance = GetModuleHandle( 0 );
	windowClass.lpszMenuName = MAKEINTRESOURCE( IDR_MENU1 );
	windowClass.lpszClassName = L"YaPyN_Editor";

	return (::RegisterClassEx( &windowClass ) != 0);
}

bool YaPyN_Editor::Create()
{
	CreateWindowEx( 0,
		L"YaPyN_Editor",
		L"YaPyN Editor v1.0",
		WS_EX_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_SYSMENU | WS_VSCROLL | ES_AUTOHSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		GetModuleHandle( 0 ),
		this );

	createToolbar();
	CellResult::checkHandle( handleMainWindow );
	SetScrollRange( handleMainWindow, SB_VERT, 0, 10000, FALSE );
	return (handleMainWindow != 0);
}

void YaPyN_Editor::Show( int cmdShow )
{
	ShowWindow( handleMainWindow, cmdShow );
	for( auto window = childrensWindow.begin(); window != childrensWindow.end(); ++window ) {
		window->Show( cmdShow );
	}
}

void YaPyN_Editor::OnNCCreate( HWND hwnd )
{
	handleMainWindow = hwnd;
}

void YaPyN_Editor::OnCreate()
{
	createCell();
}

void YaPyN_Editor::OnPaint()
{
	InvalidateRect( handleMainWindow, NULL, FALSE );
	PAINTSTRUCT paintStruct;
	::BeginPaint( handleMainWindow, &paintStruct );

	HBRUSH brush;
	brush = CreateSolidBrush( colorActiveCell );
	::FillRect( paintStruct.hdc, &paintStruct.rcPaint, brush );
	::EndPaint( handleMainWindow, &paintStruct );

	RECT rect;
	::GetClientRect( handleMainWindow, &rect );

	RECT toolbarRect;
	::GetClientRect( handleToolbar, &toolbarRect );

	int currentTop = rect.top + (toolbarRect.bottom - toolbarRect.top) + sizeBetweenCells;
	for( auto window = childrensWindow.begin(); window != childrensWindow.end(); ++window ) {
		LONG leftBorder = rect.left + marginLeftRightCells;
		LONG width = rect.right - rect.left - 2 * marginLeftRightCells;

		::SetWindowPos( window->getHandle(), HWND_TOP, leftBorder, currentTop, width, window->getHeight(), 0 );
		currentTop += sizeBetweenCells + window->getHeight();

		if( window->isResult() ) {
			leftBorder = rect.left + 2 * marginLeftRightCells;
			width = rect.right - rect.left - 4 * marginLeftRightCells;

			::SetWindowPos( window->getHandleOfResult(), HWND_TOP, leftBorder, currentTop, width, window->getHeightOfResult(), 0 );
			currentTop += sizeBetweenCells + window->getHeightOfResult();
		}
	}

	// SetScrollRange(handleMainWindow, SB_VERT, 0, 100, TRUE);

	//Подсвечивает activeCell - нужно для того, чтобы проверять, что activeCell на нужном сell'е
	//PAINTSTRUCT paintStruct2;
	//BeginPaint(activeCell->getHandle(), &paintStruct2);
	//brush = CreateSolidBrush(RGB(0, 250, 0));
	//FillRect(paintStruct2.hdc, &paintStruct2.rcPaint, brush);
	//EndPaint(activeCell->getHandle(), &paintStruct2);
}

void YaPyN_Editor::OnSize()
{
	SendMessage( handleToolbar, TB_AUTOSIZE, 0, 0 );
}

void YaPyN_Editor::OnDestroy()
{
	PostQuitMessage( SuccessDestroyWindowValue );
}

bool YaPyN_Editor::OnClose()
{
	if( changed ) {
		askToSave( textForExit );
	} else {
		switch( MessageBox( handleMainWindow, L"Вы действительно хотите выйти?", L"Завершение работы", MB_YESNO | MB_ICONWARNING ) ) {
			case IDNO:
			{
				return false;
			}
			case IDYES:
			{
				return true;
			}
		}
	}
	return true;
}

void YaPyN_Editor::OnCommand( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( HIWORD( wParam ) == 0 ) {
		switch( LOWORD( wParam ) ) {
			case ID_FILE_NEW:
			{
				if( changed ) {
					if( !askToSave( textForNewFile ) ) {
						break;
					}
				}
				clearCells();
				createCell();
				break;
			}
			case ID_FILE_EXIT:
			{
				SendMessage( hWnd, WM_CLOSE, wParam, lParam );
				break;
			}
			case ID_FILE_SAVE:
			{
				if( saveFile() ) {
					changed = false;
				}
				break;
			}
			case ID_FILE_OPEN:
			{
				if( changed ) {
					if( !askToSave( textForNewFile ) ) {
						break;
					}
				}
				loadFile();
				break;
			}
			case ID_CELL_ADD:
			{
				createCell();
				break;
			}
			case ID_CELL_DELETE:
			{
				if( MessageBox( handleMainWindow, L"Вы действительно хотите удалить ячейку?",
					L"Удаление ячейки", MB_YESNO | MB_ICONWARNING ) == IDYES ) {
					deleteCell();
				}
				break;
			}
			case ID_CELL_UP:
			{
				moveCell( true );
				break;
			}
			case ID_CELL_DOWN:
			{
				moveCell( false );
				break;
			}
			case ID_CELL_RUN:
			{
				runCell();
				break;
			}
			default:
			{
				break;
			}
		}
	} else {
		switch( HIWORD( wParam ) ) {
			case EN_CHANGE:
			{
				changed = true;
				break;
			}
			case EN_UPDATE:
			{
				resizeCell( reinterpret_cast<HWND>(lParam) );
				break;
			}
			case EN_SETFOCUS:
			{
				OnCellClick();
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void YaPyN_Editor::OnCellClick()
{
	HWND handle = ::GetFocus();
	auto cell = handlesAndCells.find( handle );
	if( cell != handlesAndCells.end() ) {
		activeCell = cell->second;
	}
	InvalidateRect( handleMainWindow, NULL, FALSE );
}

LRESULT YaPyN_Editor::OnCtlColorEdit( WPARAM wParam, LPARAM lParam )
{
	HDC hdc = reinterpret_cast<HDC>(wParam);
	HBRUSH hbr = 0;
	if( lParam == reinterpret_cast<long>(GetFocus()) ) {
		hbr = CreateSolidBrush( RGB( 255, 255, 0 ) );
		SetBkColor( hdc, RGB( 255, 255, 0 ) );
	}
	return reinterpret_cast<LRESULT>(hbr);
}

void YaPyN_Editor::createToolbar()
{

	const int bitmapSize = 16;

	HINSTANCE hInstance = ::GetModuleHandle( 0 );

	handleToolbar = CreateToolbarEx( handleMainWindow, WS_CHILD | WS_VISIBLE | CCS_TOP, 1,
		0, HINST_COMMCTRL, IDB_STD_SMALL_COLOR, NULL, 0, 0, 0, 0, 0, sizeof( TBBUTTON ) );

	//Enable multiple image lists
	SendMessage( handleToolbar, CCM_SETVERSION, (WPARAM)5, 0 );

	//Add icons from default imagelist
	TBBUTTON tbb_buildin[] = {
		{ STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0 },
		{ STD_FILEOPEN, ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0 },
		{ STD_FILESAVE, ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0 },
	};
	SendMessage( handleToolbar, (UINT)TB_ADDBUTTONS, _countof( tbb_buildin ), (LPARAM)&tbb_buildin );

	//Create custom imagelist
	HIMAGELIST hImageList = ImageList_Create( bitmapSize, bitmapSize, ILC_COLOR16 | ILC_MASK, 0, 0 );
	ImageList_Add( hImageList, LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_PLUS ) ), NULL );
	ImageList_Add( hImageList, LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_DELETE ) ), NULL );
	ImageList_Add( hImageList, LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_UP ) ), NULL );
	ImageList_Add( hImageList, LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_DOWN ) ), NULL );
	ImageList_Add( hImageList, LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_RUN ) ), NULL );
	SendMessage( handleToolbar, TB_SETIMAGELIST, (WPARAM)1, (LPARAM)hImageList );

	TBBUTTON tbb[] =
	{
		{ MAKELONG( 0, 1 ), ID_CELL_ADD, TBSTATE_ENABLED, TBSTYLE_BUTTON },
		{ MAKELONG( 1, 1 ), ID_CELL_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON },
		{ MAKELONG( 2, 1 ), ID_CELL_UP, TBSTATE_ENABLED, TBSTYLE_BUTTON },
		{ MAKELONG( 3, 1 ), ID_CELL_DOWN, TBSTATE_ENABLED, TBSTYLE_BUTTON },
		{ MAKELONG( 4, 1 ), ID_CELL_RUN, TBSTATE_ENABLED, TBSTYLE_BUTTON },
	};

	SendMessage( handleToolbar, (UINT)TB_ADDBUTTONS, _countof( tbb ), (LPARAM)&tbb );
}

bool YaPyN_Editor::saveFile()
{
	wchar_t file[maxSizeForFileName];
	OPENFILENAME openFileName = {};
	openFileName.lStructSize = sizeof( OPENFILENAME );
	openFileName.lpstrFile = file;
	openFileName.hwndOwner = handleMainWindow;
	openFileName.lpstrFile[0] = '\0';
	openFileName.nMaxFile = sizeof( file );

	bool result;
	if( result = GetSaveFileName( &openFileName ) ) {

		std::wofstream fout;
		fout.open( file );

		for( auto it = childrensWindow.begin(); it != childrensWindow.end(); ++it ) {
			std::wstring text = it->getText();
			fout << cellBeginSymbol << text << cellEndSymbol << std::endl;
			/* Или не храним результат, или обдумать новый формат хранения.
			if( it->isResult() ) {
				text = it->getResultText();
				fout << cellBeginSymbol << text << cellEndSymbol << std::endl;
			}
			*/
		}
		fout.close();
	}
	return result;
}

bool YaPyN_Editor::loadFile()
{
	clearCells();

	wchar_t file[maxSizeForFileName];
	OPENFILENAME openFileName = {};
	openFileName.lStructSize = sizeof( OPENFILENAME );
	openFileName.lpstrFile = file;
	openFileName.hwndOwner = handleMainWindow;
	openFileName.lpstrFile[0] = '\0';
	openFileName.nMaxFile = sizeof( file );

	bool result;
	if( result = GetOpenFileName( &openFileName ) ) {
		std::ifstream fin;
		fin.open( file );
		if( !fin ) {
			MessageBox( handleMainWindow, L"Выберите другой файл!", L"Нет такого файла!", MB_OK | MB_ICONWARNING );
			fin.close();
			return false;
		}
		while( !fin.eof() ) {
			std::string text;
			getline( fin, text, cellEndSymbol );
			int text_begin = text.find( cellBeginSymbol );
			if( text_begin != -1 ) {
				text = text.substr( text_begin + 1 );
				std::wstring wtext( text.begin(), text.end() );
				createCell( wtext );
			}
		}
		fin.close();
		InvalidateRect( handleMainWindow, NULL, FALSE );
	}
	return result;
}

bool YaPyN_Editor::askToSave( const wchar_t* text )
{
	LPCWSTR textLPCWSTR = reinterpret_cast<LPCWSTR>((const_cast<wchar_t*>(text)));
	switch( MessageBox( handleMainWindow, L"Вы ввели текст. Сохранить?", textLPCWSTR, MB_YESNOCANCEL | MB_ICONWARNING ) ) {
		case IDYES:
		{
			return saveFile();
		}
		case IDNO:
		{
			return true;
		}
		case IDCANCEL:
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
}

void YaPyN_Editor::createCell()
{
	activeCell = childrensWindow.emplace( activeCell == childrensWindow.end() ? childrensWindow.end() : ++activeCell, CellWindow() );
	activeCell->Create( handleMainWindow );
	handlesAndCells.insert( std::make_pair( activeCell->getHandle(), activeCell ) );
	SendMessage( handleMainWindow, WM_SIZE, 0, 0 );
}

void YaPyN_Editor::createCell( std::wstring text )
{
	createCell();
	::SetWindowText( activeCell->getHandle(), (LPWSTR)text.c_str() );
	resizeCell( activeCell->getHandle() );
	InvalidateRect( handleMainWindow, NULL, FALSE );
}

void YaPyN_Editor::deleteCell()
{
	if( activeCell != childrensWindow.end() ) {
		HWND hwnd = activeCell->getHandle();
		CellResult::checkHandle( hwnd );
		DestroyWindow( activeCell->getHandleOfResult() );
		DestroyWindow( hwnd );
		auto oldCell = activeCell;
		auto nextCell = activeCell;
		++nextCell;
		activeCell = (nextCell != childrensWindow.end()
			? nextCell
			: (activeCell != childrensWindow.begin()
				? --activeCell
				: childrensWindow.end()));
		childrensWindow.erase( oldCell );
		handlesAndCells.erase( handlesAndCells.find( hwnd ) );
		SendMessage( handleMainWindow, WM_SIZE, 0, 0 );
		if( activeCell != childrensWindow.end() ) {
			SetFocus( activeCell->getHandle() );
		}
	} else {
		MessageBox( handleMainWindow, L"Выберите ячейку!", L"Не выбрана ячейка", MB_OK | MB_ICONWARNING );
	}
	InvalidateRect( handleMainWindow, NULL, FALSE );
}

// direct == true, если вверх, false - иначе
void YaPyN_Editor::moveCell( bool direct )
{
	auto dangerousCell = activeCell;
	if( direct ) {
		dangerousCell = childrensWindow.begin();
	} else {
		dangerousCell = childrensWindow.end();
		--dangerousCell;
	}
	if( activeCell != dangerousCell ) {
		auto prevCell = activeCell;
		if( direct ) {
			--activeCell;
		} else {
			++activeCell;
		}
		std::swap( *activeCell, *prevCell );
		handlesAndCells[activeCell->getHandle()] = activeCell;
		handlesAndCells[prevCell->getHandle()] = prevCell;
		InvalidateRect( handleMainWindow, NULL, FALSE );
	}
}

void YaPyN_Editor::resizeCell( HWND handleCell )
{
	activeCell = handlesAndCells.find( handleCell )->second;

	if( activeCell->changeHeight( getCountsOfStrings( handleCell ) ) ) {
		InvalidateRect( handleMainWindow, NULL, FALSE );
		//SendMessage(handleMainWindow, WM_SIZE, 0, 0);
	}
}

void YaPyN_Editor::clearCells()
{
	unsigned int countOfCells = childrensWindow.size();
	for( unsigned int i = 0; i < countOfCells; ++i ) {
		deleteCell();
	}
	activeCell = childrensWindow.end();
	childrensWindow.clear();
	handlesAndCells.clear();
}

void YaPyN_Editor::runCell()
{
	if( activeCell != childrensWindow.end() ) {
		activeCell->setResult();
		::SetWindowText( activeCell->getHandleOfResult(), (LPWSTR)resultText );
		SendMessage( handleMainWindow, WM_SIZE, 0, 0 );
		InvalidateRect( handleMainWindow, NULL, FALSE );
		activeCell++;
		if( activeCell != childrensWindow.end() ) {
			SetFocus( activeCell->getHandle() );
		} else {
			activeCell--;
		}
	}
}

const int YaPyN_Editor::SuccessDestroyWindowValue = 0;

unsigned int YaPyN_Editor::getCountsOfStrings( HWND handleCell )
{
	unsigned int countOfN = 0;
	unsigned int indexOfN = 0;
	unsigned int countOfLongStrings = 0;

	int length = SendMessage( handleCell, WM_GETTEXTLENGTH, 0, 0 );
	std::shared_ptr<wchar_t> text_ptr( new wchar_t[length + 1] );
	wchar_t* text = text_ptr.get();
	SendMessage( handleCell, WM_GETTEXT, length + 1, reinterpret_cast<LPARAM>(text) );

	if( text[0] = '\n' ) {
		++countOfN;
	}

	for( int i = 1; i < wcslen( text ); ++i ) {
		if( text[i] == '\n' ) {
			++countOfN;
			indexOfN = i;
		}
	}

	return countOfN;
}

LRESULT YaPyN_Editor::windowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( message == WM_NCCREATE ) {
		YaPyN_Editor* window = reinterpret_cast<YaPyN_Editor*> ((reinterpret_cast<CREATESTRUCT*>(lParam))->lpCreateParams);
		SetLastError( 0 );
		SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(window) );
		if( GetLastError() ) {
			return GetLastError();
		}
		window->OnNCCreate( hwnd );
		return DefWindowProc( hwnd, message, wParam, lParam );
	}

	YaPyN_Editor* window = reinterpret_cast<YaPyN_Editor*>(GetWindowLongPtr( hwnd, GWLP_USERDATA ));
	switch( message ) {
		case WM_CREATE:
		{
			window->OnCreate();
			return DefWindowProc( hwnd, message, wParam, lParam );
		}
		case WM_PAINT:
		{
			window->OnPaint();
			return DefWindowProc( hwnd, message, wParam, lParam );
		}
		case WM_SIZE:
		{
			window->OnSize();
			return DefWindowProc( hwnd, message, wParam, lParam );
		}
		case WM_CLOSE:
		{
			if( window->OnClose() ) {
				::PostQuitMessage( 0 );
				return DefWindowProc( hwnd, message, wParam, lParam );
			} else {
				return 0;
			}
		}
		case WM_COMMAND:
		{
			window->OnCommand( hwnd, message, wParam, lParam );
			return DefWindowProc( hwnd, message, wParam, lParam );
		}
		case WM_DESTROY:
		{
			window->OnDestroy();
			return SuccessDestroyWindowValue;
		}
		case WM_CTLCOLOREDIT:
		{
			return window->OnCtlColorEdit( wParam, lParam );
		}
		case WM_VSCROLL:
		{
			//MessageBox(window->handleMainWindow, L"sdfsdf", L"sss", MB_OK);
		}
		default:
		{
			return DefWindowProc( hwnd, message, wParam, lParam );
		}
	}
}
