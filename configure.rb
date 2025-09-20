#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#
#  TOPPERS Software
#      Toyohashi Open Platform for Embedded Real-Time Systems
# 
#  Copyright (C) 2001-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2006-2020 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
# 
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
# 
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
# 
#  $Id: configure.rb 985 2020-07-18 08:37:24Z ertl-hiro $
# 

Encoding.default_external = 'utf-8'
require "optparse"
require "fileutils"

#  Option definitions
#
#  -T <target>			Target name (required)
#  -a <appldirs>		Application directory names (multiple options allowed.
#						Default is the sample directory)
#  -A <applname>		Application program name (default is sample1)
#  -t					Exclude the main object file from the link target
#  -c <cfgfile>			System configuration file name
#						(.cfg file name)
#  -C <cdlflle>			Component description file (.cdl file)
#  -U <applobjs>		Additional object files for the application
#						(specify .o file names. Multiple files can be specified)
#  -S <syssvcobjs>		System service object file (specify .o file name.
#						Multiple files can be specified)
#  -B <bannerobj>		Banner display object file (specify .o file names)
#  -L <kernel_lib>		Directory name of the kernel library (libkernel.a)
#						(If omitted, the kernel library will also be made)
#  -f					Specifies whether to compile the kernel function-by-function.
#  -D <srcdir>			Directory where the kernel source is located.
#  -l <srclang>			Programming language (currently, only C and C++ are supported).
#  -m <tempmakefile>	Specify the Makefile template file name
#						(default is Makefile in the sample directory)
#  -d <objdir>			Directory name for intermediate object files and dependency files
#						(default is objs)
#  -w					Does not use TECS.
#  -W <tecsdir>			Directory name of TECS related files
#						(default is tecsgen under the source file directory)
#  -r					Specify whether to use the trace logging sample code
#  -V <devtooldir>		Directory where development tools (compilers, etc.) are located.
#  -R <ruby>			Pathname of Ruby (if explicitly specified).
#  -g <cfg>				Pathname of the configurator (cfg).
#  -G <tecsgen>			Pathname of the TECS generator (tecsgen).
#  -o <options>			Compiler options (added to COPTS)
#  -O <options>			Symbol definition options (added to CDEFs)
#  -k <options>			Linker options (added to LDFLAGS)
#  -b <options>			Linker options (added to LIBS)

#  Usage example (1)
#
#  % ../configure.rb -T ct11mpcore_gcc -O "-DTOPPERS_USE_QEMU" \
#					-A perf1 -a ../test -S "test_svc.o histogram.o"
#
#  Usage example (2)
#
#  % ../configure.rb -T macosx_gcc -L .
#	The application program is sample1.
#
#  Usage example (3)
#
#  % ../configure.rb -T ct11mpcore_gcc -O "-DTOPPERS_USE_QEMU" -A tSample2 -t
#	The application program will be the TECS version of the sample program.
#
#  Usage example (4)
#
#  % ../configure.rb -T ct11mpcore_gcc PRC_NUM=4
#	Define PRC_NUM to be 4.

#
#  Initializing variables
#
$target = nil
$appldirs = []
$applname = nil
$option_t = false
$cfgfile = nil
$cdlfile = nil
$applobjs = []
$syssvcobjs = []
$bannerobj = nil
$kernel_lib = ""
$kernel_funcobjs = ""
$srcdir = nil
$srclang = "c"
$tempmakefile = nil
$objdir = "objs"
$omit_tecs = ""
$tecsdir = nil
$enable_trace = ""
$devtooldir = ""
$ruby = "ruby"
$cfg = nil
$tecsgen = nil
$copts = []
$cdefs = []
$ldflags = []
$libs = []

#
#  Option Processing
#
OptionParser.new(nil, 22) do |opt|
  opt.on("-T target",		"taget name (mandatory)") do |val|
    $target = val
  end
  opt.on("-a appldirs",		"application directories") do |val|
    $appldirs += val.split(/\s+/)
  end
  opt.on("-A applname",		"application program name") do |val|
    $applname = val
  end
  opt.on("-t",				"TECS is used for application development") do |val|
    $option_t = true
  end
  opt.on("-c cfgfile",		"system configuration file") do |val|
    $cfgfile = val
  end
  opt.on("-C cdlfile",		"component description file") do |val|
    $cdlfile = val
  end
  opt.on("-U applobjs",		"additional application object files") do |val|
    $applobjs += val.split(/\s+/)
  end
  opt.on("-S syssvcobjs",	"system service object files") do |val|
    $syssvcobjs += val.split(/\s+/)
  end
  opt.on("-B bannerobj",	"banner display object file") do |val|
    $bannerobj = val
  end
  opt.on("-L kernel_lib",	"directory of built kernel library") do |val|
    $kernel_lib = val
  end
  opt.on("-f", "each function is compiled separately in kernel") do |val|
    $kernel_funcobjs = "true"
  end
  opt.on("-D srcdir",		"path of source code directory") do |val|
    $srcdir = val
  end
  opt.on("-l srclang",		"programming language (C or C++)") do |val|
    $srclang = val
  end
  opt.on("-m tempmakefile", "template file of Makefile") do |val|
    $tempmakefile = val
  end
  opt.on("-d objdir",		"relocatable object file directory") do |val|
    $objdir = val
  end
  opt.on("-w",				"TECS is not used at all") do |val|
    $omit_tecs = "true"
  end
  opt.on("-W tecsdir",		"path of TECS file directory") do |val|
    $tecsdir = val
  end
  opt.on("-r",				"use the sample code for trace log") do |val|
    $enable_trace = "true"
  end
  opt.on("-V devtooldir",	"development tools directory") do |val|
    $devtooldir = val
  end
  opt.on("-R ruby",			"path of ruby command") do |val|
    $ruby = val
  end
  opt.on("-g cfg",			"path of configurator") do |val|
    $cfg = val
  end
  opt.on("-G tecsgen",		"path of TECS generator") do |val|
    $tecsgen = val
  end
  opt.on("-o options",		"compiler options") do |val|
    $copts += val.split(/\s+/)
  end
  opt.on("-O options",		"symbol definition options") do |val|
    $cdefs += val.split(/\s+/)
  end
  opt.on("-k options",		"linker options") do |val|
    $ldflags += val.split(/\s+/)
  end
  opt.on("-b options",		"linker options for linking libraries") do |val|
    $libs += val.split(/\s+/)
  end
  opt.parse!(ARGV)
end

#
#  Returns the object filename extension
#
def GetObjectExtension
  if /cygwin/ =~ RUBY_PLATFORM
    return("exe")
  else
    return("")
  end
end

#
#  Default values ​​of variables (default values ​​of string variables are given during initialization)
#
if $appldirs.empty?
  $appldirs.push("\$(SRCDIR)/sample")
end
$applname ||= "sample1"
$cfgfile ||= $applname + ".cfg"
$cdlfile ||= $applname + ".cdl"
$applobjs.unshift($applname + ".o") if !$option_t
$bannerobj ||= ($omit_tecs == "") ? "tBannerMain.o" : "banner.o"
if $srcdir.nil?
  # Extract the source directory name
  if /^(.*)\/configure/ =~ $0
    $srcdir = $1
  else
    $srcdir = Dir.pwd
  end
end
if /^\// =~ $srcdir
  $srcabsdir = $srcdir
else
  $srcabsdir = Dir.pwd + "/" + $srcdir
end
$tempmakefile ||= $srcdir + "/sample/Makefile"
$tecsdir ||= "\$(SRCDIR)/tecsgen"
$cfg ||= $ruby + " \$(SRCDIR)/cfg/cfg.rb"
$tecsgen ||= $ruby + " \$(TECSDIR)/tecsgen.rb"

#
#  -T option and checking target dependency directories
#
if $target.nil?
  puts("configure.rb: -T option is mandatory")
elsif !File.directory?($srcdir + "/target/" + $target)
  puts("configure.rb: #{$srcdir}/target/#{$target} not exist.")
  $target = nil
end

if $target.nil?
  puts("Installed targets are:")
  Dir.glob($srcdir + "/target/[a-zA-Z0-9]*").each do |target|
    target.sub!($srcdir + "/target/", "")
    puts("\t" + target)
  end
  abort
end

#
#  Creating a variable table
#
$vartable = Hash.new("")
$vartable["TARGET"] = $target
$vartable["APPLDIRS"] = $appldirs.join(" ")
$vartable["APPLNAME"] = $applname
$vartable["CFGFILE"] = $cfgfile
$vartable["CDLFILE"] = $cdlfile
$vartable["APPLOBJS"] = $applobjs.join(" ")
$vartable["SYSSVCOBJS"] = $syssvcobjs.join(" ")
$vartable["BANNEROBJ"] = $bannerobj
$vartable["KERNEL_LIB"] = $kernel_lib
$vartable["KERNEL_FUNCOBJS"] = $kernel_funcobjs
$vartable["SRCDIR"] = $srcdir
$vartable["SRCABSDIR"] = $srcabsdir
$vartable["SRCLANG"] = $srclang
$vartable["OBJDIR"] = $objdir
$vartable["OMIT_TECS"] = $omit_tecs
$vartable["TECSDIR"] = $tecsdir
$vartable["ENABLE_TRACE"] = $enable_trace
$vartable["DEVTOOLDIR"] = $devtooldir
$vartable["RUBY"] = $ruby
$vartable["CFG"] = $cfg
$vartable["TECSGEN"] = $tecsgen
$vartable["COPTS"] = $copts.join(" ")
$vartable["CDEFS"] = $cdefs.join(" ")
$vartable["LDFLAGS"] = $ldflags.join(" ")
$vartable["LIBS"] = $libs.join(" ")
$vartable["OBJEXT"] = GetObjectExtension()
ARGV.each do |arg|
  if /^([A-Za-z0-9_]+)\s*\=\s*(.*)$/ =~ arg
    $vartable[$1] = $2
  else
    $vartable[arg] = true
  end
end

#
#  Convert files
#
def convert(inFileName, outFileName)
  puts("Generating #{outFileName} from #{inFileName}.\n")
  if (File.file?(outFileName))
    puts("#{outFileName} exists.  Save as #{outFileName}.bak.\n")
    FileUtils.move(outFileName, outFileName + ".bak")
  end

  begin
    inFile = File.open(inFileName)
    outFile = File.open(outFileName, "w")
  rescue Errno::ENOENT, Errno::EACCES => ex
    abort(ex.message)
  end

  inFile.each do |line|
    line.chomp!
    while line.sub!(/\@\(([A-Za-z0-9_]+)\)/) {|var| $vartable[$1]} do end
    outFile.print(line,"\n")
  end

  inFile.close
  outFile.close
end

#
#  Generate Makefile
#
convert($tempmakefile, "Makefile")

#
#  Creating directories for intermediate object files and dependency files
#
if !File.directory?($objdir)
  Dir.mkdir($objdir)
end
