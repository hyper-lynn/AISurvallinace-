#!/bin/env python

import os, sys, stat, shutil, glob
from Tkinter import *

def on_rmtree_error( func, path, exec_info ) :
	if os.access( path, os.R_OK ) :
		os.chmod( path, stat.S_IWRITE )
		func( path )

def do_rmtree( path ) :
	shutil.rmtree( path, onerror = on_rmtree_error )
	if os.access( path, os.R_OK ) :
		return 1
	return 0

def globcopy( pattern, dst ) :
	for fn in glob.glob( pattern ) :
		shutil.copy( fn, dst )

def do_build_pkg( target ) :
	# <1> Set Build Option
	before_cmd = "devenv ../DssBaseLib.sln /Rebuild \"Debug|Win32\" /project "
	after_cmd = ""
	fn_d = "_d"
	if target == "win32-vs2005-debug" :
		before_cmd = "devenv ../DssBaseLib.sln /Rebuild \"Debug|Win32\" /project "
		after_cmd = ""
		fn_d = "_d"
	elif target == "win32-vs2005-release" :
		before_cmd = "devenv ../DssBaseLib.sln /Rebuild \"Release|Win32\" /project "
		after_cmd = ""
		fn_d = ""
	elif target == "win64-vs2005-debug" :
		before_cmd = "devenv ../DssBaseLib.sln /Rebuild \"Debug|x64\" /project "
		after_cmd = ""
		fn_d = "_d"
	elif target == "win64-vs2005-release" :
		before_cmd = "devenv ../DssBaseLib.sln /Rebuild \"Release|x64\" /project "
		after_cmd = ""
		fn_d = ""
	elif target == "win32-vs2015-debug" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\MSBuild\\14.0\\Bin;\
D:\\Program Files\\MSBuild\\14.0\\Bin;\
E:\\Program Files\\MSBuild\\14.0\\Bin;\
F:\\Program Files\\MSBuild\\14.0\\Bin;\
G:\\Program Files\\MSBuild\\14.0\\Bin;\
C:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
D:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
E:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
F:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
G:\\Program Files (x86)\\MSBuild\\14.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2015.sln /p:Configuration=Debug;Platform=Win32 /t:"
		after_cmd = ":Rebuild "
		fn_d = "_d"
	elif target == "win32-vs2015-release" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\MSBuild\\14.0\\Bin;\
D:\\Program Files\\MSBuild\\14.0\\Bin;\
E:\\Program Files\\MSBuild\\14.0\\Bin;\
F:\\Program Files\\MSBuild\\14.0\\Bin;\
G:\\Program Files\\MSBuild\\14.0\\Bin;\
C:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
D:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
E:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
F:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
G:\\Program Files (x86)\\MSBuild\\14.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2015.sln /p:Configuration=Release;Platform=Win32 /t:"
		after_cmd = ":Rebuild "
		fn_d = ""
	elif target == "win64-vs2015-debug" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\MSBuild\\14.0\\Bin;\
D:\\Program Files\\MSBuild\\14.0\\Bin;\
E:\\Program Files\\MSBuild\\14.0\\Bin;\
F:\\Program Files\\MSBuild\\14.0\\Bin;\
G:\\Program Files\\MSBuild\\14.0\\Bin;\
C:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
D:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
E:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
F:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
G:\\Program Files (x86)\\MSBuild\\14.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2015.sln /p:Configuration=Debug;Platform=x64 /t:"
		after_cmd = ":Rebuild "
		fn_d = "_d"
	elif target == "win64-vs2015-release" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\MSBuild\\14.0\\Bin;\
D:\\Program Files\\MSBuild\\14.0\\Bin;\
E:\\Program Files\\MSBuild\\14.0\\Bin;\
F:\\Program Files\\MSBuild\\14.0\\Bin;\
G:\\Program Files\\MSBuild\\14.0\\Bin;\
C:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
D:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
E:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
F:\\Program Files (x86)\\MSBuild\\14.0\\Bin;\
G:\\Program Files (x86)\\MSBuild\\14.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2015.sln /p:Configuration=Release;Platform=x64 /t:"
		after_cmd = ":Rebuild "
		fn_d = ""
	elif target == "win32-vs2017-debug" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2017.sln /p:Configuration=Debug;Platform=x86 /t:"
		after_cmd = ":Rebuild "
		fn_d = "_d"
	elif target == "win32-vs2017-release" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2017.sln /p:Configuration=Release;Platform=x86 /t:"
		after_cmd = ":Rebuild "
		fn_d = ""
	elif target == "win64-vs2017-debug" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2017.sln /p:Configuration=Debug;Platform=x64 /t:"
		after_cmd = ":Rebuild "
		fn_d = "_d"
	elif target == "win64-vs2017-release" :
		path = os.environ["PATH"]
		os.environ["PATH"] = "C:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
D:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
E:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
F:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;\
G:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Enterprise\\MSBuild\\15.0\\Bin;" + path
		before_cmd = "msbuild ../DssBaseLib_2017.sln /p:Configuration=Release;Platform=x64 /t:"
		after_cmd = ":Rebuild "
		fn_d = ""
	else :
		print "bad target"
		return 1

	####################################
	####	Custom Section Begin
	####################################

	dst_dir = "DssBaseLib" + fn_d
	if do_rmtree( dst_dir ) != 0 :
		print "rmtree failed"
		return 1
	if os.access( dst_dir + ".zip", os.R_OK ) :
		os.remove( dst_dir + ".zip" )
	
	# <2> Build Target From Source
	prjs = [ "DOAXBase", "libdsl", "libdsl_static", "dslalien", "dslalien_static", "libdsl_ssl" ]
	for prj in prjs :
		cmd = before_cmd + prj + after_cmd
		if os.system( cmd ) != 0 :
			print "build prj " + prj + " failed"
			return 1

	# <3> Package Target
	# TODO : do rmtree again, should not need. but mkdir may failed without it
	do_rmtree( dst_dir )
	os.mkdir( dst_dir )
	subdirs = [ "AX_API", "HTTP", "RTP", "RTSP", "tinyxml", "TPLayer", "Utils", "libdsl", "jsondsl", "pugixmldsl", "sqlitedsl", "zlibdsl", "curl"]
	for d in subdirs :
		os.mkdir( dst_dir + "/" + d )

	os.mkdir( dst_dir + "/libdsl/ESB" );
	globcopy( "../DOAXBase/AX_API/*.h", dst_dir + "/AX_API" )
	globcopy( "../DOAXBase/AX_API/*.inl", dst_dir + "/AX_API" )
	globcopy( "../DOAXBase/HTTP/*.h", dst_dir + "/HTTP" )
	globcopy( "../DOAXBase/RTP/*.h", dst_dir + "/RTP" )
	globcopy( "../DOAXBase/RTSP/*.h", dst_dir + "/RTSP" )
	globcopy( "../DOAXBase/tinyxml/*.h", dst_dir + "/tinyxml" )
	globcopy( "../DOAXBase/TPLayer/*.h", dst_dir + "/TPLayer" )
	globcopy( "../DOAXBase/Utils/*.h", dst_dir + "/Utils" )
	globcopy( "../libdsl/*.h", dst_dir + "/libdsl" )
	globcopy( "../libdsl/jsondsl/*.h", dst_dir + "/jsondsl" )
	globcopy( "../libdsl/pugixmldsl/*.h*", dst_dir + "/pugixmldsl" )
	globcopy( "../libdsl/ESB/*.h*", dst_dir + "/libdsl/ESB" )
	globcopy( "../dslalien/dslalien.h", dst_dir )
	globcopy( "../dslalien/sqlitedsl/*.h", dst_dir + "/sqlitedsl" )
	globcopy( "../dslalien/zlibdsl/zconf.h", dst_dir + "/zlibdsl" )
	globcopy( "../dslalien/zlibdsl/zlib.h", dst_dir + "/zlibdsl" )
	globcopy( "../dslalien/curl/include/curl/*.h", dst_dir + "/curl" )
	globcopy( "../dslalien/curl/ftp_opt.h", dst_dir + "/curl" )
	globcopy( "../libdsl_ssl/DSHA.h", dst_dir + "/libdsl" )
	globcopy( "../libdsl_ssl/AESCryption.h", dst_dir + "/libdsl" )
	globcopy( "../libdsl_ssl/RSACryption.h", dst_dir + "/libdsl" )
	globcopy( "../libdsl_ssl/DSecureUtil.h", dst_dir + "/libdsl" )

	# log4cplus
	#os.mkdir( dst_dir + "/log4cplus/boost" )
	#os.mkdir( dst_dir + "/log4cplus/config" )
	#os.mkdir( dst_dir + "/log4cplus/helpers" )
	#os.mkdir( dst_dir + "/log4cplus/internal" )
	#os.mkdir( dst_dir + "/log4cplus/spi" )
	#os.mkdir( dst_dir + "/log4cplus/thread" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/*.h", dst_dir + "/log4cplus" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/boost/*.h", dst_dir + "/log4cplus/boost" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/config/*.h", dst_dir + "/log4cplus/config" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/helpers/*.h", dst_dir + "/log4cplus/helpers" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/internal/*.h", dst_dir + "/log4cplus/internal" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/spi/*.h", dst_dir + "/log4cplus/spi" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/thread/*.h", dst_dir + "/log4cplus/thread" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/*.hxx", dst_dir + "/log4cplus" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/boost/*.hxx", dst_dir + "/log4cplus/boost" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/config/*.hxx", dst_dir + "/log4cplus/config" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/helpers/*.hxx", dst_dir + "/log4cplus/helpers" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/internal/*.hxx", dst_dir + "/log4cplus/internal" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/spi/*.hxx", dst_dir + "/log4cplus/spi" )
	#globcopy( "../dslalien/log4cplus/include/log4cplus/thread/*.hxx", dst_dir + "/log4cplus/thread" )

	rmfs = [ "/libdsl/StdAfx.h", "/libdsl/svn_version.h" ]
	for f in rmfs :
		os.remove( dst_dir + f );

	os.mkdir( dst_dir + "/html" );
	os.mkdir( dst_dir + "/html/jstree" );
	globcopy( "../demo/html/*.html", dst_dir + "/html" );
	globcopy( "../demo/html/jstree/*.*", dst_dir + "/html/jstree" );

	# put these in release package as example for other module
	globcopy( "../vs2005_dsl_debug.vsprops", dst_dir )
	globcopy( "../vs2005_dsl_release.vsprops", dst_dir )
	globcopy( "build_pkg*.*", dst_dir )
	globcopy( "test_pkg*.*", dst_dir )
	globcopy( "upload_pkg*.*", dst_dir )
	globcopy( "gen_svninfo_header.bat", dst_dir )
	globcopy( "../Depend/build_depend*.*", dst_dir )
	globcopy( "../Depend/update_depend*.*", dst_dir )

	for prj in prjs :
		globcopy( "../bin/" + prj + fn_d + ".lib", dst_dir )
		globcopy( "../bin/" + prj + fn_d + ".pdb", dst_dir )

	globcopy( "../bin/" + "dslalien" + fn_d + ".dll", dst_dir )
	globcopy( "../bin/" + "libdsl" + fn_d + ".dll", dst_dir )

	if target[0:5] == "win32" :
		globcopy( "../dbghelp/dbghelp.dll", dst_dir )
	else :
		globcopy( "../dbghelp/x64/dbghelp.dll", dst_dir )

	####################################
	####	Custom Section End
	####################################

	globcopy( "../Depend/Version.xml", dst_dir )
	shutil.make_archive( dst_dir, "zip", "./", dst_dir )
	return 0


class gui_builder :
	def __init__(self) :
		top = Tk()
		self.top = top
		top.grid()

		lb1 = Label( top, text="Target Type" )
		lb1.grid( row=0, column=0 )
		self.var_target = StringVar()
		avail_targets = [ "win32-vs2005-debug", "win32-vs2005-release",
				"win64-vs2005-debug", "win64-vs2005-release",
				"win32-vs2015-debug", "win32-vs2015-release",
				"win64-vs2015-debug", "win64-vs2015-release",
				"win32-vs2017-debug", "win32-vs2017-release",
				"win64-vs2017-debug", "win64-vs2017-release" ]
		self.var_target.set( "win32-vs2005-debug" )
		om1 = OptionMenu( top, self.var_target, *avail_targets )
		om1.grid( row=0, column=1 )

		btn = Button( top, text="Build", command=self.build_pkg )
		btn.grid( row=1, column=0, columnspan=2, padx=10, pady=5 )

		self.var_info = StringVar()
		self.info = Label( top, textvariable=self.var_info )
		self.info.grid( row=2, column=0, columnspan=2, pady=5 )

	def run(self) :
		self.top.mainloop()

	def build_pkg(self) :
		self.var_info.set( "building, please wait ... " )
		self.info.update()
		ret = do_build_pkg( self.var_target.get() )
		if ret == 0 :
			self.var_info.set( "OK -- build pkg success" )
		else :
			self.var_info.set( "ERR -- build pkg failed" )

if __name__ == "__main__" :
	if len(sys.argv) >= 2 :
		ret = do_build_pkg( sys.argv[1] )
		if ret == 0 :
			print "OK -- build pkg success"
		else :
			print "ERR -- build pkg failed"
		sys.exit(ret)
	elif os.name == "nt" :
		gbd = gui_builder()
		gbd.run()
	else :
		print "Usage: build_pkg [target_type]"
		sys.exit(1)

