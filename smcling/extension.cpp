/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Sample Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.hpp"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */
cling::Interpreter *g_pInterp;
SMCling g_ClingInterp;		/**< Global singleton for extension's main interface */
SMEXT_LINK(&g_ClingInterp);

bool SMCling::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	char buffer[512]={0};
	g_pSM->BuildPath(Path_SM, buffer, sizeof(buffer)-1, "/cling_plugins/cling_includes/");
	if( !libsys->PathExists(buffer) ) {
		return false;
	}
	
	// Shit's loaded, check for a directory and C++ source files to exec.
	std::vector<std::string> cling_args_storage;
	cling_args_storage.push_back("SMCling_Ext");
	
	// TODO: get this from env
	//cling_args_storage.push_back("-I/home/wlavrijsen/rootdev/root/etc");
	cling_args_storage.push_back("-I/home/kevin/SourceCodes/C++/Embedding Cling");
	
	
	std::vector< const char* > interp_args;
	{
		std::vector< std::string >::const_iterator iarg;
		for( iarg = cling_args_storage.begin() ; iarg != cling_args_storage.end() ; ++iarg )
			interp_args.push_back( iarg->c_str() );
	}

	// TODO: get this from env
	//const char *llvm_resource_dir = "/home/wlavrijsen/rootdev/root/etc/cling";
	const char *llvm_resource_dir = "/home/kevin/SourceCodes/C++/Embedding Cling/";
	g_pInterp = new cling::Interpreter(interp_args.size(), &(interp_args[0]), llvm_resource_dir);
	
	{
		char szIncludePath[512]={0};
		g_pSM->BuildPath(Path_SM, szIncludePath, sizeof(szIncludePath)-1, "/cling_plugins/cling_includes/");
		if( !libsys->PathExists(szIncludePath) ) {
			g_pSM->Format(error, maxlength-1, "SMCling C++ Interpreter failed to Load. Did not detect \'/cling_plugins/cling_includes/\' Include path.");
			return false;
		}
		g_pInterp->AddIncludePath(szIncludePath);
		g_pInterp->AddIncludePath(".");
	}
	
	class cling::Value val;
	enum cling::Interpreter::CompilationResult res = g_pInterp->process("int i = 5;", &val);
	printf("SMCLING C++ Plugin :: Loaded Successfully! -- res -> %i | value == %lli\n", res==cling::Interpreter::kSuccess, val.getLL());
	return true;
}

void SMCling::SDK_OnUnload()
{
	// Shit's being unloaded, close directories and kill processes used by interpreter.
	delete g_pInterp; g_pInterp = nullptr;
}
