.SILENT:

all: debug

debug:
	cmake -H. -Bbuild/debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug -- -j2

release:
	cmake -H. -Bbuild/release -DCMAKE_BUILD_TYPE=Release
	cmake --build build/release -- -j2

clean:
	rm -rf bin/*
	rm -rf build/*

clean_logs:
	rm -f nw*

