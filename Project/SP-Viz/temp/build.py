import os
import platform

# (1)==================== COMMON CONFIGURATION OPTIONS ======================= #
COMPILER="clang++ -std=c++14"   # The compiler we want to use
                                #(You may try g++ if you have trouble)
SOURCE="../src/*.cpp"    # Where the source code lives
EXECUTABLE="SP-Visualizer"        # Name of the final executable
# ======================= COMMON CONFIGURATION OPTIONS ======================= #

# (2)=================== Platform specific configuration ===================== #
# For each platform we need to set the following items

# Arguments needed for our program (Add others as you see fit)
ARGUMENTS="-D MAC" # -D is a #define sent to the preprocessor.
# Which directories do we want to include.

INCLUDE_DIR="-I ../include/ -I ../lib/SDL2.framework/Headers -I ../lib/SDL2_ttf.framework/Headers -I ../lib/SDL2_image.framework/Headers -I ../lib/SDL2_mixer.framework/Headers"
# What libraries do we want to include
LIBRARIES="-F ../lib -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer"

# (3)====================== Building the Executable ========================== #
# Build a string of our compile commands that we run in the terminal
compileString=COMPILER+" "+ARGUMENTS+" -o "+EXECUTABLE+" "+" "+INCLUDE_DIR+" "+SOURCE+" "+LIBRARIES
# Print out the compile string
# This is the command you can type
print "============v (Command running on terminal) v==========================="
print "Compilng on: "+platform.system()
print compileString
print "========================================================================"
# Run our command
os.system(compileString)
# ========================= Building the Executable ========================== #

