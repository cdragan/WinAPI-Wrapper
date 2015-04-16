// (c) 2001	Microsoft Corporation

function OnFinish(selProj, selObj)
{
	try
	{
		ValidateSymbolValues();

		var	strProjectPath = wizard.FindSymbol("PROJECT_PATH");
		var	strProjectName = wizard.FindSymbol("PROJECT_NAME");

		var	bEmptyProject =	wizard.FindSymbol("EMPTY_PROJECT");

		selProj	= CreateProject(strProjectName,	strProjectPath);
		selProj.Object.Keyword = "WinAPIProj";

		AddCommonConfig(selProj, strProjectName);
		var	strAppType = GetAppType();
		AddSpecificConfig(selProj, strProjectName, bEmptyProject, strAppType);

		AddFilters(selProj);

		if (!bEmptyProject)
		{
			var	strCodePage	= wizard.FindSymbol("CODE_PAGE");
			if (strCodePage	== "1252")
				wizard.AddSymbol("ABOUTBOX_FONT_SIZE", "8");
			else
				wizard.AddSymbol("ABOUTBOX_FONT_SIZE", "9");

			var	InfFile	= CreateInfFile();
			var	Pch	= wizard.FindSymbol("PRE_COMPILED_HEADER");

			if (!Pch)
			{
				AddFilesToProject(selProj, strProjectName, InfFile);
				SetNoPchSettings(selProj);
			}
			else
			{
				AddFilesToProject(selProj, strProjectName, InfFile);
				SetCommonPchSettings(selProj);
			}

			InfFile.Delete();
		}
		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length !=	0)
			SetErrorInfo(e);
		return e.number
	}
}

function SetFileProperties(projfile, strName)
{
	return false;
}

function DoOpenFile(strTarget)
{
	return false;
}

function GetTargetName(strName,	strProjectName,	strResPath,	strHelpPath)
{
	try
	{
		var	strTarget =	strName;

		if (strName	== "readme.txt")
			strTarget =	"ReadMe.txt";
		if (strName	== "resource.h")
			strTarget =	"resource.h";

		if (strName	== "small.ico")
		{
			strTarget =	"small.ico";
		}
		if (strName.substr(0, 4) ==	"root")
		{
			var	strlen = strName.length;
			strTarget =	strProjectName + strName.substr(4, strlen -	4);

		}
		return strTarget;
	}
	catch(e)
	{
		throw e;
	}
}

function GetAppType()
{
	try
	{
		var	strAppType = "";
		if (wizard.FindSymbol("SDI_APP"))
			strAppType = "SDI";
		else
		{
			if (wizard.FindSymbol("MDI_APP"))
				strAppType = "MDI";
			else
			{
				if (wizard.FindSymbol("DIALOG_APP"))
					strAppType = "DIALOG";
			}
		}
		return strAppType;
	}
	catch(e)
	{
		throw e;
	}
}

function AddSpecificConfig(proj, strProjectName, bEmptyProject,	strAppType)
{
	try
	{
		var	config = proj.Object.Configurations("Debug");
		config.CharacterSet	= charSetMBCS;

		var	Pch	= wizard.FindSymbol("PRE_COMPILED_HEADER");
		var	CLTool = config.Tools("VCCLCompilerTool");
	//	CLTool.PrecompiledHeaderFile = "$(OutDir)/"	+ strProjectName + ".pch";
		if (!Pch)
		{
			CLTool.UsePrecompiledHeader	= pchGenerateAuto;
		}

		CLTool.RuntimeLibrary =	rtSingleThreadedDebug;

		var	strDefines = GetPlatformDefine(config);
		strDefines += "_DEBUG;_WINDOWS";

		var	bUseSTL	= wizard.FindSymbol("USE_STL");
		if (!bUseSTL)
			strDefines += ";SKIP_STL";

		var	bPureWrapper = wizard.FindSymbol("PURE_WRAPPER");
		if (bPureWrapper)
			strDefines += ";PURE_WRAPPER";

		CLTool.PreprocessorDefinitions = strDefines;

		CLTool.DebugInformationFormat =	debugEditAndContinue;

		var	LinkTool = config.Tools("VCLinkerTool");
		LinkTool.ProgramDatabaseFile = "$(OutDir)/"	+ strProjectName + ".pdb";
		LinkTool.GenerateDebugInformation =	true;
		LinkTool.LinkIncremental = linkIncrementalYes;

		LinkTool.SubSystem = subSystemWindows;

		LinkTool.OutputFile	= "$(OutDir)/" + strProjectName	+ ".exe";

		if (bPureWrapper)
			LinkTool.AdditionalDependencies	= "WinAPIpd.lib	comctl32.lib ws2_32.lib";
		else
			LinkTool.AdditionalDependencies	= "WinAPId.lib comctl32.lib ws2_32.lib";

		config = proj.Object.Configurations.Item("Release");
		config.CharacterSet	= charSetMBCS;

		var	CLTool = config.Tools("VCCLCompilerTool");
		if (!Pch)
		{
			CLTool.UsePrecompiledHeader	= pchGenerateAuto;
		}

		CLTool.RuntimeLibrary =	rtSingleThreaded;
		CLTool.InlineFunctionExpansion = expandOnlyInline;

		var	strDefines = GetPlatformDefine(config);
		strDefines += "NDEBUG;_WINDOWS";

		if (!bUseSTL)
			strDefines += ";SKIP_STL";

		if (bPureWrapper)
			strDefines += ";PURE_WRAPPER";

		CLTool.DebugInformationFormat =	debugEnabled;

		CLTool.PreprocessorDefinitions = strDefines;

		var	LinkTool = config.Tools("VCLinkerTool");
		LinkTool.GenerateDebugInformation =	true;
		LinkTool.LinkIncremental = linkIncrementalNo;

		LinkTool.SubSystem = subSystemWindows;

		LinkTool.OutputFile	= "$(OutDir)/" + strProjectName	+ ".exe";

		if (bPureWrapper)
			LinkTool.AdditionalDependencies	= "WinAPIp.lib comctl32.lib ws2_32.lib";
		else
			LinkTool.AdditionalDependencies	= "WinAPI.lib comctl32.lib ws2_32.lib";
	}
	catch(e)
	{
		throw e;
	}
}

function ValidateSymbolValues()
{
	try {
		var pure_wrapper = wizard.FindSymbol("PURE_WRAPPER");
		if (pure_wrapper)
		{
			wizard.AddSymbol("ON_GENERIC",true);
			wizard.AddSymbol("ON_CREATE",true);
			wizard.AddSymbol("ON_MOUSE_DOWN",false);
			wizard.AddSymbol("ON_MOUSE_UP",false);
			wizard.AddSymbol("ON_MOUSE_DBL_CLK",false);
		}

		var dialog_app = wizard.FindSymbol("DIALOG_APP");
		if (dialog_app)
		{
			wizard.AddSymbol("ON_COMMAND",true);
			wizard.AddSymbol("ON_PAINT",false);
			wizard.AddSymbol("ON_KEY_UP_DOWN",false);
			wizard.AddSymbol("CUSTOM_WINDOW_CLASS",false);
			wizard.AddSymbol("MENU",false);
			wizard.AddSymbol("TOOLBAR",false);
			wizard.AddSymbol("REBAR",false);
			wizard.AddSymbol("STATUSBAR",false);
		}

		var menu = wizard.FindSymbol("MENU");
		var toolbar = wizard.FindSymbol("TOOLBAR");
		if (!toolbar)
		{
			wizard.AddSymbol("REBAR",false);
		}
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
    try
    {
        // Add the folders to your project
        var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
        var group = proj.Object.AddFilter('Source Files');
        group.Filter = strSrcFilter;
    }
    catch(e)
    {
        throw e;
    }
}
