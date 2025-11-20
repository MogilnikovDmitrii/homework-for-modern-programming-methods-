namespace DmMog {
	struct MenuItem {
		const char* const title;
		void (*func)();
	};
}
