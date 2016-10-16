#include "stdafx.h"
#include "Trie.h"


namespace Yapynb {

	const CTrie::TPosition CTrie::FromRoot = 0;

	const CTrie::TPosition CTrie::InvalidPosition =
		std::numeric_limits<CTrie::TPosition>::max()
		;

	const CTrie::TPosition CTrie::MaxCompletions =
		std::numeric_limits<CTrie::TPosition>::max()
		;

	CTrie::CTrie()
	{
		NewNode();
	}

	CTrie::TPosition CTrie::Root() const
	{
		return FromRoot;
	}

	bool CTrie::IsValidPosition( TPosition pos ) const
	{
		return pos < Nodes.size();
	}

	CTrie::TPosition CTrie::Go( TChar by, TPosition from ) const
	{
		if( !IsValidPosition( from ) ) {
			return InvalidPosition;
		}
		auto it = Nodes[from].Next.find( by );
		return it == Nodes[from].Next.end() ? InvalidPosition : it->second;
	}

	bool CTrie::IsTerminal( TPosition pos ) const
	{
		return IsValidPosition( pos ) && Nodes[pos].Terminal;
	}

	void CTrie::EnsureTerminal( TPosition pos )
	{
		Nodes[pos].Terminal = true;
	}

	CTrie::TPosition CTrie::Append( TChar by, TPosition from )
	{
		CTransitionMap::iterator it;
		bool success;
		std::tie( it, success ) = Nodes[from].Next.emplace( by, InvalidPosition );
		if( success ) {
			it->second = NewNode();
		}
		return it->second;
	}

	CTrie::TPosition CTrie::NewNode()
	{
		size_t oldSize = Nodes.size();
		Nodes.emplace_back();
		return oldSize;
	}

}  // Yapynb
