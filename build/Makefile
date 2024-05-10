WINDOWS_TOOLCHAIN_PATH = # Leave blank if this is your current platform
LINUX_TOOLCHAIN_PATH   = # Leave blank if this is your current platform
MACOS_TOOLCHAIN_PATH   = # Leave blank if this is your current platform

CMAKE_OPTIONS 				= 
CMAKE_WINDOWS_OPTIONS = 
CMAKE_LINUX_OPTIONS 	= 
CMAKE_MACOS_OPTIONS 	= 

GENERATOR = Unix Makefiles


.PHONY: all clean gen_debug gen_release gen_release_info

all: gen_debug gen_release gen_release_info

gen_debug:
	@echo "Generating Debug..."

	cd debug/macos;	cmake ../../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=$(MACOS_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_MACOS_OPTIONS)
	cd debug/linux; cmake ../../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=$(LINUX_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_LINUX_OPTIONS) 
	cd debug/win64; cmake ../../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=$(WINDOWS_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_WINDOWS_OPTIONS)
	
	touch debug/macos/.gitkeep
	touch debug/linux/.gitkeep
	touch debug/win64/.gitkeep

gen_release:
	@echo "Generating Release..."

	cd release/macos; cmake ../../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$(MACOS_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_MACOS_OPTIONS)
	cd release/linux; cmake ../../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$(LINUX_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_LINUX_OPTIONS)
	cd release/win64; cmake ../../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$(WINDOWS_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_WINDOWS_OPTIONS)

	touch release/macos/.gitkeep
	touch release/linux/.gitkeep
	touch release/win64/.gitkeep

gen_release_info:
	@echo "Generating Release with debug info..."

	cd release_info/macos; cmake ../../.. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=$(MACOS_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_MACOS_OPTIONS)
	cd release_info/linux; cmake ../../.. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=$(LINUX_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_LINUX_OPTIONS)
	cd release_info/win64; cmake ../../.. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=$(WINDOWS_TOOLCHAIN_PATH) -G"$(GENERATOR)" $(CMAKE_OPTIONS) $(CMAKE_WINDOWS_OPTIONS)

	touch release_info/macos/.gitkeep
	touch release_info/linux/.gitkeep
	touch release_info/win64/.gitkeep

clean:
	rm -f debug/macos/* debug/linux/* debug/win64/*
	rm -f release/macos/* release/linux/* release/win64/*
	rm -f release_info/macos/* release_info/linux/* release_info/win64/*

	# Create a file in all of the dirs to make sure git doesn't remove them
	touch debug/macos/.gitkeep
	touch debug/linux/.gitkeep
	touch debug/win64/.gitkeep

	touch release/macos/.gitkeep
	touch release/linux/.gitkeep
	touch release/win64/.gitkeep

	touch release_info/macos/.gitkeep
	touch release_info/linux/.gitkeep
	touch release_info/win64/.gitkeep
