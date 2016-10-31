#pragma once
#include "CellWindow.h"
#include "CellRunner.h"

class YaPyN_Editor {
public:

	YaPyN_Editor();

	static bool RegisterClass();

	bool Create();

	void Show( int cmdShow );

protected:

	void OnNCCreate( HWND hwnd );
	void OnCreate();
	void OnPaint();
	void OnSize();
	void OnDestroy();
	bool OnClose();
	void OnCommand( HWND hWnd, WPARAM wParam, LPARAM lParam );
	void OnCellClick();
	void OnAddPict();
	LRESULT OnCtlColorEdit( WPARAM wParam, LPARAM lParam );

private:		
	std::unique_ptr<CellRunner> cellRunner;

	HWND handleMainWindow;
	HWND handleToolbar;
	std::list<CellWindow> childrensWindow;
	std::list<CellWindow>::iterator activeCell;
	std::map<HWND, std::list<CellWindow>::iterator> handlesAndCells;

	static const int sizeBetweenCells;
	static const int marginLeftRightCells;

	bool changed;

	std::vector<HBITMAP> buttonsBitmaps;

	void createToolbar();

	bool saveFile();
	bool loadFile();
	bool askToSave( const wchar_t* text );

	void createCell();
	void createCell( std::wstring text );
	void deleteCell();
	void moveCell( bool direct );
	void resizeCell( HWND handleCell );
	void clearCells();
	void runCell();
	void resetInterpetor();
	void ExceptionBox(const std::exception& e );
	BOOL getMessageResult = 0;

	static const int SuccessDestroyWindowValue;


	unsigned int getCountsOfStrings( HWND handleCell );

	static LRESULT __stdcall windowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
};
