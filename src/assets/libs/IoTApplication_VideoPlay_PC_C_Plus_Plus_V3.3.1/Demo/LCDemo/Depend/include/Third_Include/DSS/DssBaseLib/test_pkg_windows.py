#!/bin/env python

import os, sys, shutil, glob
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

def do_test_pkg( target ) :
	# <1> Set Build Option
	bd_param = "Debug|Win32"
	fn_d = "_d"
	if target == "win32-vs2005-debug" :
		bd_param = "Debug|Win32"
		fn_d = "_d"
	elif target == "win32-vs2005-release" :
		bd_param = "Release|Win32"
		fn_d = ""
	elif target == "win64-vs2005-debug" :
		bd_param = "Debug|x64"
		fn_d = "_d"
	elif target == "win64-vs2005-release" :
		bd_param = "Release|x64"
		fn_d = ""
	else :
		print "bad target"
		return 1

	####################################
	####	Custom Section Begin
	####################################

	# <2> Build Test Target
	cmd = "devenv ../DssBaseLib.sln /Rebuild \"" + bd_param + "\" /project test "
	if os.system( cmd ) != 0 :
		print "build test prj failed"
		return 1

	# <3> Run Test Target
	cmd = "..\\bin\\test" + fn_d + ".exe"
	if os.system( cmd ) != 0 :
		print "run test failed"
		return 1

	####################################
	####	Custom Section End
	####################################

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
				"win64-vs2005-debug", "win64-vs2005-release" ]
		self.var_target.set( "win32-vs2005-debug" )
		om1 = OptionMenu( top, self.var_target, *avail_targets )
		om1.grid( row=0, column=1 )

		btn = Button( top, text="Test", command=self.test_pkg )
		btn.grid( row=1, column=0, columnspan=2, padx=10, pady=5 )

		self.var_info = StringVar()
		self.info = Label( top, textvariable=self.var_info )
		self.info.grid( row=2, column=0, columnspan=2, pady=5 )

	def run(self) :
		self.top.mainloop()

	def test_pkg(self) :
		self.var_info.set( "building and testing, please wait ... " )
		self.info.update()
		ret = do_test_pkg( self.var_target.get() )
		if ret == 0 :
			self.var_info.set( "OK -- test pkg success" )
		else :
			self.var_info.set( "ERR -- test pkg failed" )

if __name__ == "__main__" :
	if len(sys.argv) >= 2 :
		ret = do_test_pkg( sys.argv[1] )
		if ret == 0 :
			print "OK -- test pkg success"
		else :
			print "ERR -- test pkg failed"
		sys.exit(ret)
	elif os.name == "nt" :
		gbd = gui_builder()
		gbd.run()
	else :
		print "Usage: test_pkg [target_type]"
		sys.exit(1)

