src= ../..

.PHONY: micro all clean
module: micro

TARGETS = bulk random repeat mmap_bulk mmap_bulk_populate je_bulk je_random je_repeat

CXXFLAGS = -std=c++20 -g -shared
JE_FLAGS = -I $(src)/modules/jemalloc/upstream/jemalloc/include/jemalloc -DJEMALLOC $(CXXFLAGS)

all: micro

micro: $(TARGETS)

je_%: %.cpp
	$(CXX) $(JE_FLAGS) -o $@ $< $(src)/modules/jemalloc/upstream/jemalloc/lib/libjemalloc.a

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

