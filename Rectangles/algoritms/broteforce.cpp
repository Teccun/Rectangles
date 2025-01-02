#include "broteforce.h"

void broteforce::execute() {	

	std::vector<rectangle> rect_inter = rectangles;
	std::vector<rectangle> all_rect = rect_inter;

	std::vector<rectangle> tmp;
	char flag_1 = 0;
	char flag_2 = 0;
	do {
		tmp.clear();
		float x1, x2, x3, x4, y1, y2, y3, y4;
		Coord LD, RU;
		for (int i = 0; i < rect_inter.size(); i++) {

			x1 = rect_inter[i].getCordLeftDown().X;
			y1 = rect_inter[i].getCordLeftDown().Y;
			x2 = rect_inter[i].getCordRightUp().X;
			y2 = rect_inter[i].getCordRightUp().Y;
			
			for (int j = 0; j < rect_inter.size(); j++) {
				if (i != j) {
					if (rect_inter[i].areRectanglesIntersecting(rect_inter[j])) {
						
						x3 = rect_inter[j].getCordLeftDown().X;
						y3 = rect_inter[j].getCordLeftDown().Y;
						x4 = rect_inter[j].getCordRightUp().X;
						y4 = rect_inter[j].getCordRightUp().Y;

						LD.X = std::max(x1, x3);
						LD.Y = std::max(y1, y3);
						RU.X = std::min(x2, x4);
						RU.Y = std::min(y2, y4);

						rectangle new_rect(LD, RU);

						/*
						Проверка на присутствие в данной итерации 
						Если присутствует, то... то ничего не делаем
						Не происходит добавления в следующую итерацию
						За это отвечает флаг2 
						*/

						for (int f = 0; f < tmp.size(); f++) {
							if (new_rect == tmp[f]) {
								//tmp[f].decInter();
								flag_2 = 1;
								break;
							}
						}

						/*
						Не верно работает счетчик пересечений. Нужно сделать так, что бы работал верно
						Проверить лучше данный код
						*/

						for (int f = 0; f < all_rect.size(); f++) {
							if (new_rect == all_rect[f]) {
								if (!flag_2)
									all_rect[f].incrInter();
								flag_1 = 1;
								break;
							}
						}

						/*
						Нужно задуматься над хэш-таблицей. Нужно посмотреть, можно ли хранить данные там, ключ - прямоугольник, а данные - количество пересечений.
						*/

						if (flag_2 == 0)
							tmp.push_back(new_rect);
						else
							flag_2 = 0;

						if (flag_1 == 0)
							all_rect.push_back(new_rect);
						else
							flag_1 = 0;
					}
				}
			}
		}
		if (!tmp.empty())
			rect_inter = tmp;
	} while (!tmp.empty());

	for (int i = 0; i < all_rect.size(); i++) {
		//std::cout << all_rect[i].get_intersection() << "\n";
		if (all_rect[i].get_intersection() >= k)
			std::cout << all_rect[i] << " " << all_rect[i].get_intersection() << '\n';
	}
}