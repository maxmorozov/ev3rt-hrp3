#!/usr/bin/env ruby -Eutf-8 -w
# -*- coding: utf-8 -*-
#
#  TOPPERS Configurator by Ruby
#
#  Copyright (C) 2015 by FUJI SOFT INCORPORATED, JAPAN
#  Copyright (C) 2015-2019 by Embedded and Real-Time Systems Laboratory
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
#  $Id: cfg.rb 170 2019-02-13 07:45:58Z ertl-hiro $
#

if $0 == __FILE__
  TOOL_ROOT = File.expand_path(File.dirname(__FILE__)) + "/"
  $LOAD_PATH.unshift(TOOL_ROOT)
end

require "pp"
require "csv"
require "optparse"
require "pstore"
require "GenFile.rb"
require "SRecord.rb"

#
#  Constant definitions
#
# common
VERSION = "1.4.0"

# cfg1_out関係
CFG1_PREFIX         = "TOPPERS_cfg_"
CFG1_MAGIC_NUM      = "TOPPERS_magic_number"
CFG1_SIZEOF_SIGNED  = "TOPPERS_sizeof_signed_t"
CFG1_SIZEOF_INTPTR  = "TOPPERS_sizeof_intptr_t"
CFG1_SIZEOF_CHARPTR = "TOPPERS_sizeof_char_ptr_t"
CFG1_OUT_C          = "cfg1_out.c"
CFG1_OUT_DB         = "cfg1_out.db"
CFG1_OUT_SREC       = "cfg1_out.srec"
CFG1_OUT_SYMS       = "cfg1_out.syms"
CFG1_OUT_TIMESTAMP  = "cfg1_out.timestamp"
CFG1_OUT_TARGET_H   = "target_cfg1_out.h"

# cfg2_out related
CFG2_OUT_DB        = "cfg2_out.db"

# cfg3_out related
CFG3_OUT_DB        = "cfg3_out.db"

#
#  Error occurrence flag
#
$errorFlag = false

#
#  Error/Warning Display Function
#
# General error message (processing is interrupted)
def error_exit(message, location = "")
  location += " " if location != ""
  abort("#{location}error: #{message}")
end

# General error message (processing continues)
def error(message, location = "")
  location += " " if location != ""
  STDERR.puts("#{location}error: #{message}")
  $errorFlag = true
end

# General warning signs
def warning(message, location = "")
  location += " " if location != ""
  STDERR.puts("#{location}warning: #{message}")
end

# Error parsing system configuration file
$noParseError = 0
def parse_error(cfgFile, message)
  error(message, "#{cfgFile.getFileName()}:#{cfgFile.getLineNo}:")
  if ($noParseError += 1) >= 10
    abort("too many errors emitted, stopping now")
  end
end

# System configuration file parsing warnings
def parse_warning(cfgFile, message)
  warning(message, "#{cfgFile.getFileName()}:#{cfgFile.getLineNo}:")
end

#
#  Error/warning display function when processing static API
#
# To allow for concise descriptions of errors/warnings during static API processing, 
# descriptions beginning with % or %% in the message are expanded as follows:
#	%label → #{params[:label]}
#	%%label → label `#{params[:label]}'
#
# Expanding error/warning messages
def expand_message(message, params)
  result = message.dup
  while /%%(\w+)\b/ =~ result
    param = $1
    paramVal = params[param.to_sym].to_s
    result.sub!(/%%#{param}\b/, "#{param} `#{paramVal}'")
  end
  while /%(\w+)\b/ =~ result
    param = $1
    paramVal = params[param.to_sym].to_s
    result.sub!(/%#{param}\b/, paramVal)
  end
  return(result)
end

# Static API processing error
def error_api(params, message)
  error(expand_message(message, params), \
			"#{params[:_file_]}:#{params[:_line_]}:")
end

# Static API processing warnings
def warning_api(params, message)
  warning(expand_message(message, params), \
			"#{params[:_file_]}:#{params[:_line_]}:")
end

# Static API processing error (with error code)
def error_ercd(errorCode, params, message)
  error_api(params, "#{errorCode}: #{message}")
end

# Parameter Error
def error_wrong(errorCode, params, symbol, wrong)
  error_ercd(errorCode, params, "%%#{symbol} is #{wrong} in %apiname")
end

def error_wrong_id(errorCode, params, symbol, objid, wrong)
  error_ercd(errorCode, params, "%%#{symbol} is #{wrong} " \
	             					"in %apiname of %#{objid}")
end

def error_wrong_sym(errorCode, params, symbol, symbol2, wrong)
  error_ercd(errorCode, params, "%%#{symbol} is #{wrong} " \
									"in %apiname of %%#{symbol2}")
end

# Invalid parameter error
def error_illegal(errorCode, params, symbol)
  error_ercd(errorCode, params, "illegal %%#{symbol} in %apiname")
end

def error_illegal_id(errorCode, params, symbol, objid)
  error_ercd(errorCode, params, "illegal %%#{symbol} " \
	             					"in %apiname of %#{objid}")
end

def error_illegal_sym(errorCode, params, symbol, symbol2)
  error_ercd(errorCode, params, "illegal %%#{symbol} " \
									"in %apiname of %%#{symbol2}")
end

#
#  Extending the String class (creating/expanding double-quoted strings)
#
class String
  #
  #  Creating double-quoted strings
  #
  def quote
    result = ""
    self.chars do |c|
      case c
      when "'"
        result += "\\\'"
      when "\""
        result += "\\\""
      when "\0"
        result += "\\0"
      when "\a"
        result += "\\a"
      when "\b"
        result += "\\b"
      when "\f"
        result += "\\f"
      when "\n"
        result += "\\n"
      when "\r"
        result += "\\r"
      when "\t"
        result += "\\t"
      when "\v"
        result += "\\v"
      when "\\"
        result += "\\\\"
      else
        result += c
      end
    end
    return("\"" + result + "\"")
  end

  #
  #  Interpolating double-quoted strings
  #
  def unquote
    if /^\"(.*)\"$/m =~ self
      str = $1
      result = ""
      while (/^(.*)\\(.*)$/m =~ str)
        result += $1
        str = $2
        case str
        when /^[aA](.*)$/m
          result += "\a"
          str = $1
        when /^[bB](.*)$/m
          result += "\b"
          str = $1
        when /^[fF](.*)$/m
          result += "\f"
          str = $1
        when /^[nN](.*)$/m
          result += "\n"
          str = $1
        when /^[rR](.*)$/m
          result += "\r"
          str = $1
        when /^[tT](.*)$/m
          result += "\t"
          str = $1
        when /^[vV](.*)$/m
          result += "\v"
          str = $1
        when /^[xX]([0-9a-fA-F][0-9a-fA-F]?)(.*)$/m
          result += $1.hex
          str = $2
        when /^([0-7][0-7]?[0-7]?)(.*)$/m
          result += $1.oct
          str = $2
        when /^\\(.*)$/m
          result += "\\"
          str = $1
        end
      end
      return(result + str)
    else
      return(self.dup)
    end
  end
end

#
#  Definition of the NumStr class (a string added to a number)
#
class NumStr
  def initialize(val, str = val.to_s)
    @val = val
    @str = str
  end

  # Returns numerical information
  def val
    return @val
  end
  alias_method :to_i, :val

  # Returns string information
  def str
    return @str
  end
  alias_method :to_s, :str

  # Comparison is made using numerical information
  def ==(other)
    @val == other
  end
  def !=(other)
    @val != other
  end
  def <=>(other)
    @val <=> other
  end

  # Comparisons when used as hash keys are also performed using numerical information.
  def eql?(other)
    @val == other
  end

  # Overrides hash value definitions as well
  def hash
    return @val.hash
  end

  # Allows operations with numeric classes
  def coerce(other)
    if other.kind_of?(Numeric)
      return other, @val
    else
      raise
    end
  end

  # Creating double-quoted strings
  def quote
    str.quote
  end

  # Interpolating double-quoted strings
  def unquote
    str.unquote
  end

  # Display when pp
  def pretty_print(q)
    q.text("[#{@val}(=0x#{@val.to_s(16)}),")
    @str.pretty_print(q)
    q.text("]")
  end

  # Send undefined methods to @val
  def method_missing(*method)
    @val.send(*method)
  end
end

#
#  Loading symbol files
#
#  The following methods correspond to symbol files generated by GNU nm:
#  If you want to support a different tool, you can rewrite this method.
#
def ReadSymbolFile(symbolFileName)
  begin
    symbolFile = File.open(symbolFileName)
  rescue Errno::ENOENT, Errno::EACCES => ex
    abort(ex.message)
  end

  symbolAddress = {}
  symbolFile.each do |line|
    # Space-delimited decomposition
    fields = line.split(/\s+/)

    # Exclude rows that are not in three columns
    if fields.size == 3
      symbolAddress[fields[2]] = fields[0].hex
    end
  end
  symbolFile.close
  return(symbolAddress)
end

#
#  Define a get value symbol as a global variable
#
def DefineSymbolValue
  $symbolValueTable.each do |symbolName, symbolData|
    if symbolData.has_key?(:VALUE)
      eval("$#{symbolName} = #{symbolData[:VALUE]}")
      if symbolData.has_key?(:NUMSTRVAR)
        eval("$#{symbolData[:NUMSTRVAR]} = " \
					"NumStr.new(symbolData[:VALUE], symbolData[:EXPR])")
      end
    end
  end
end

#
#  Finding files in the include path
#
def SearchFilePath(fileName)
  if File.exist?(fileName)
    # Exists in the specified file path
    return fileName
  elsif /^\./ =~ fileName
    # If a relative path is specified and not found, it is assumed not to exist 
    # (prevents unintended files from being targeted).
    return nil
  else
    # Check whether a file exists in each include path
    $includeDirectories.each do |includeDirectory|
      path = includeDirectory + "/" + fileName
      # If found, return the relative path.
      if File.exist?(path)
        return path
      end
    end
    return nil
  end
end

#
#  Search for and load the specified generation script (trb file)
#
def IncludeTrb(fileName)
  filePath = SearchFilePath(fileName)
  if filePath.nil?
    error_exit("`#{fileName}' not found")
  else
    load(filePath)
  end
end

#
#  Generate include directives (#include)
#
def GenerateIncludes(genFile)
  $cfgFileInfo.each do |cfgInfo|
    if cfgInfo.has_key?(:DIRECTIVE)
      genFile.add(cfgInfo[:DIRECTIVE])
    end
  end
end

#
#  Pass 3 processing
#
def Pass3
  #
  #  Read the information passed from path 2 from the file
  #
  db = PStore.new(CFG2_OUT_DB)
  db.transaction(true) do
    db.roots.each do |var|
      eval("$#{var} = db[:#{var}]")
    end
  end

  #
  #  Define a get value symbol as a global variable
  #
  DefineSymbolValue()

  #
  #  Run the generated script (trb file)
  #
  $trbFileNames.each do |trbFileName|
    IncludeTrb(trbFileName)
  end

  #
  #  Generate the information to be passed to pass 4 in a file
  #
  if !$omitOutputDb
    db = PStore.new(CFG3_OUT_DB)
    db.transaction do
      $globalVars.each do |var|
        eval("db[:#{var}] = $#{var}")
      end
    end
  end
end

#
#  Pass 4 processing
#
def Pass4
  #
  #  Read the information passed from path 3 from the file
  #
  db = PStore.new(CFG3_OUT_DB)
  db.transaction(true) do
    db.roots.each do |var|
      eval("$#{var} = db[:#{var}]")
    end
  end

  #
  #  Define a get value symbol as a global variable
  #
  DefineSymbolValue()

  #
  #  Run the generated script (trb file)
  #
  $trbFileNames.each do |trbFileName|
    IncludeTrb(trbFileName)
  end
end

#
#  Functions for generating scripts (trb files)
#
def SYMBOL(symbol)
  if !$romSymbol.nil? && $romSymbol.has_key?($asmLabel + symbol)
    return $romSymbol[$asmLabel + symbol]
  else
    return nil
  end
end

def BCOPY(fromAddress, toAddress, size)
  if !$romImage.nil?
    copyData = $romImage.get_data(fromAddress, size)
    if !copyData.nil?
      $romImage.set_data(toAddress, copyData)
    end
  end
end

def BZERO(address, size)
  if !$romImage.nil?
    $romImage.set_data(address, "00" * size)
  end
end

def PEEK(address, size, signed=false)
  if !$romImage.nil?
    return $romImage.get_value(address, size, signed)
  else
    return nil
  end
end

#
#  Initializing global variables
#
$kernel = nil
$pass = nil
$includeDirectories = []
$trbFileNames = []
$apiTableFileNames = []
$symvalTableFileNames = []
$romImageFileName = nil
$romSymbolFileName = nil
$idInputFileName = nil
$idOutputFileName = nil
$dependencyFileName = nil
$omitOutputDb = false
$supportDomain = false
$supportClass = false

#
#  Option Processing
#
OptionParser.new("Usage: cfg.rb [options] CONFIG-FILE", 40) do |opt|
  opt.version = VERSION
  opt.release = nil
  opt.on("-k KERNEL", "--kernel KERNEL", "kernel profile name") do |val|
    $kernel = val
  end
  opt.on("-p NUM", "--pass NUM", "processing pass number") do |val|
    $pass = val
  end
  opt.on("-I DIRECTORY", "--include-directory DIRECTORY",
										 "include directory") do |val|
    $includeDirectories.push(val)
  end
  opt.on("-T TRB-FILE", "--trb-file TRB-FILE",
         "generation script (trb file)") do |val|
    $trbFileNames.push(val)
  end
  opt.on("--api-table API-TABLE-FILE", "static API table file") do |val|
    $apiTableFileNames.push(val)
  end
  opt.on("--symval-table SYMVAL-TABLE-FILE", "symbol-value table file") do |val|
    $symvalTableFileNames.push(val)
  end
  opt.on("--rom-image SREC-FILE", "rom image file (s-record)") do |val|
    $romImageFileName = val
  end
  opt.on("--rom-symbol SYMS-FILE", "rom symbol table file (nm)") do |val|
    $romSymbolFileName = val
  end
  opt.on("--id-input-file ID-FILE", "ID input file") do |val|
    $idInputFileName = val
  end
  opt.on("--id-output-file ID-FILE", "ID output file") do |val|
    $idOutputFileName = val
  end
  opt.on("-M [DEPEND-FILE]", "--print-dependencies [DEPEND-FILE]",
         "dependency file") do |val|
    $dependencyFileName = val.nil? ? "" : val
  end
  opt.on("-O", "--omit-output-db", "omit DB file output") do
    $omitOutputDb = true
  end
  opt.on("--enable-domain", "enable DOMAIN support") do
	$supportDomain = true
  end
  opt.on("--enable-class", "enable CLASS support") do
	$supportClass = true
  end
  opt.on("-v", "--version", "show version number") do
    puts(opt.ver)
    exit(0)
  end
  opt.on("-h", "--help", "show help (this)") do
    puts(opt.help)
    exit(0)
  end
  opt.parse!(ARGV)
end
$configFileNames = ARGV

#
#  Check options
#
if $pass.nil?
  # Specifying the path is mandatory
  abort("`--pass' option is mandatory")
elsif /^[1234]$/ !~ $pass
  abort("pass number `#{$pass}' is not valid")
end

# In pass 1, the static API table is required
if ($pass == "1" && $apiTableFileNames.empty?)
  abort("`--api-table' option must be specified in pass 1")
end

# A generation script (trb file) is required except for path 1.
if ($pass != "1" && $trbFileNames.empty?)
  abort("`--trb-file' must be specified except in pass 1")
end

#
#  Kernel option processing
#
case $kernel
when /^hrp/
	$supportDomain = true
when /^fmp/
	$supportClass = true
when /^hrmp/
	$supportDomain = true
	$supportClass = true
end

#
#  Importing ID number input file
#
$inputObjid = {}
if !$idInputFileName.nil?
  begin
    idInputFile = File.open($idInputFileName)
  rescue Errno::ENOENT, Errno::EACCES => ex
    abort(ex.message)
  end

  idInputFile.each do |line|
    ( objName, objidNumber ) = line.split(/\s+/)
    $inputObjid[objName] = objidNumber.to_i
  end

  idInputFile.close
end

#
#  Load the specified symbol file
#
if !$romSymbolFileName.nil?
  if File.exist?($romSymbolFileName)
    $romSymbol = ReadSymbolFile($romSymbolFileName)
  else
    error_exit("`#{$romSymbolFileName}' not found")
  end
end

#
#  Read the specified S record file
#
if !$romImageFileName.nil?
  if File.exist?($romImageFileName)
    $romImage = SRecord.new($romImageFileName)
  else
    error_exit("`#{$romImageFileName}' not found")
  end
end

#
#  Execute each process according to the path
#
case $pass
when "1"
  load("pass1.rb")
  Pass1()
when "2"
  load("pass2.rb")
  Pass2()
when "3"
  Pass3()
when "4"
  Pass4()
else
  error_exit("invalid pass: #{$pass}")
end

# Abort if an error occurs
if $errorFlag
  if ($0 == __FILE__)
    abort()
  else
    # simplecov対応
    raise()
  end
end

#
#  Print all the files you created
#
GenFile.output

# 
#  Generate a timestamp file
# 
if !$timeStampFileName.nil?
  File.open($timeStampFileName, "w").close
end
