# use this makefile to build with platformio 
#
.PHONY: all clean upload monitor lint ci

all:
	pio run

lint:
	cpplint --extensions=cpp,h,ino $(shell find . -name "*\.cpp" -o -name "*\.h" -o -name "*\.ino")

ci:
	platformio ci --lib="src/" examples/demo/demo.ino \
		--board=uno --board=esp01 --board=due

clean:
	pio run --target clean

upload:
	pio run --target upload 

monitor:
	pio device monitor

