# Author: 		Rosa Knowles 
# Created: 		11/16/2025
# Last Updated: 11/17/2025
# Description: 	Makefile for this horrible project

OUTPUT_FOLDER := out
TARGET := main

# compiles and then runs the program
run: $(OUTPUT_FOLDER)/$(TARGET).exe
	./$(OUTPUT_FOLDER)/$(TARGET).exe

# compile and then run the program
# use a redirect to store the output in a txt file
txt: $(OUTPUT_FOLDER)/$(TARGET).exe
	./$(OUTPUT_FOLDER)/$(TARGET).exe > $(OUTPUT_FOLDER)/$(TARGET).txt

# compiles the level generation library into an object file 
# packs it into a static library using the archiver command 
# removes the object files 
LEVELGEN_CPPFILES := levelgeneration/levelfloor.cpp levelgeneration/levelroom.cpp
LEVELGEN_HEADERS := levelgeneration/levelgeneration.h
LEVELGEN_OBJS := levelroom.o levelfloor.o
$(OUTPUT_FOLDER)/liblevelgen.a: $(LEVELGEN_HEADERS) $(LEVELGEN_CPPFILES)
	g++ -c $(LEVELGEN_CPPFILES)
	ar rcs $(OUTPUT_FOLDER)/liblevelgen.a $(LEVELGEN_OBJS)
	rm -f *.o

# compiles the program
$(OUTPUT_FOLDER)/$(TARGET).exe: maindriver.cpp $(OUTPUT_FOLDER)/liblevelgen.a
	g++ -Wall -o $(OUTPUT_FOLDER)/$(TARGET).exe maindriver.cpp -L ./$(OUTPUT_FOLDER) -llevelgen

# removes all compiled executables and libraries 
# also removes all compiled object files, in the event that compilation fails for something else
clean:
	rm -f $(OUTPUT_FOLDER)/$(TARGET).exe
	rm -f $(OUTPUT_FOLDER)/*.a
	rm -f *.o
	rm -f $(OUTPUT_FOLDER)/$(TARGET).txt