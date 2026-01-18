#include <iostream>
#include <memory>
#include "window.hpp"


int main(){
	std::unique_ptr<Window> keeper = std::make_unique<Window>(900, 800, "Ledger Keeper");

	keeper->drawWindow();

	return 0;
}
