# GDB Configuration for better visual debugging
set confirm off
set verbose off
set print pretty on
set print array on
set print array-indexes on
set print elements 0
set print null-stop on
set print sevenbit-strings off
set print union on
set print demangle on
set print asm-demangle on
set demangle-style gnu-v3
set print object on
set print static-members on
set print vtbl on
set print symbol-filename on
set print line-numbers on
set history filename ~/.gdb_history
set history save on
set history size 10000
set history expansion on
set disassembly-flavor intel
set pagination off

# Enable TUI mode by default when using 'gdb -tui'
# set tui border-kind ascii
# set tui active-border-mode bold-standout
# set tui border-mode reverse

# Custom commands for easier debugging
define pstack
    bt
    info registers
    info locals
end
document pstack
Print stack trace, registers, and local variables
end

define penv
    info variables
    info functions
end
document penv
Print environment variables and functions
end

# Automatically load symbols
set auto-load safe-path /

# Color settings (if your terminal supports it)
set style enabled on
set style sources on
set style disassembler on

# Show source code context
set listsize 20