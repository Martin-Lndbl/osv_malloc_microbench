src= ../..

.PHONY: micro all clean
module: micro

TARGETS = bulk random pipeline repeat memory mmap_bulk mmap_bulk_populate je_bulk je_random je_pipeline je_repeat je_memory

CXXFLAGS = -std=c++20 -g -O1
CXXFLAGS += -I../../. -I../../include -I../../arch/x64/
CXXFLAGS += -I../../build/release/gen/include
JE_FLAGS = -I $(src)/modules/jemalloc/upstream/jemalloc/include/jemalloc -DJEMALLOC $(CXXFLAGS)

all: micro

micro: $(TARGETS)

je_%: %.cpp
	$(CXX) $(JE_FLAGS) -o $@ $< $(src)/modules/jemalloc/upstream/jemalloc/lib/libjemalloc.a

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

