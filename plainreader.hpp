#ifndef PLAIN_READER_HPP
#define PLAIN_READER_HPP

struct Material
{
	enum {
		Dirt = 1<<0,
		Dirt2 = 1<<1,
		Rock = 1<<2,
		Background = 1<<3,
		SeeShadow = 1<<4,
		WormM = 1<<5
	};

	bool dirt();
	bool dirt2();
	bool rock();
	bool background();
	bool seeShadow();

	// Constructed
	bool dirtRock();
	bool anyDirt();
	bool dirtBack();
	bool worm();

	int flags;
};

#endif //PLAIN_READER_HPP
