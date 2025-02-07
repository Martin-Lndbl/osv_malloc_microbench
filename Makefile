.PHONY: micro all clean
module: micro

TARGETS = bulk random repeat mmap_bulk mmap_bulk_populate

CXXFLAGS = -std=c++20 -g

all: micro

micro: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

