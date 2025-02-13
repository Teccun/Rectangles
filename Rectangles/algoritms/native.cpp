#include "native.h"

void native::execute() {
    int numBounds = numRect * 2;
    float* xBounds = new float[numBounds];
    float* yBounds = new float[numBounds];
    int xCount = 0, yCount = 0;
    for (int i = 0; i < numRect; i++) {
        xBounds[xCount++] = rectangles_arr[i].getCordLeftDown().X;
        xBounds[xCount++] = rectangles_arr[i].getCordRightUp().X;
        yBounds[yCount++] = rectangles_arr[i].getCordLeftDown().Y;
        yBounds[yCount++] = rectangles_arr[i].getCordRightUp().Y;
        stdoper++;
    }
    
    std::sort(xBounds, xBounds + numBounds);
    std::sort(yBounds, yBounds + numBounds);
    stdoper = stdoper + 2 * (numBounds * std::log(numBounds));

    // Убираем дубликаты
    int distinctX = 0;
    for (int i = 0; i < numBounds; i++) {
        if (i == 0 || xBounds[i] != xBounds[i - 1])
            xBounds[distinctX++] = xBounds[i];
    }
    int distinctY = 0;
    for (int i = 0; i < numBounds; i++) {
        if (i == 0 || yBounds[i] != yBounds[i - 1])
            yBounds[distinctY++] = yBounds[i];
    }
    // После этого: xBounds[0..distinctX-1] и yBounds[0..distinctY-1] – уникальные границы.

    //Определяем размеры сетки.
    // Каждая "ячейка" задаётся интервалом между соседними границами.
    int gridWidth = distinctX - 1;   // число столбцов
    int gridHeight = distinctY - 1;  // число строк

    // Создаём матрицу покрытий (одномерный массив размера gridWidth * gridHeight).
    int* coverage = new int[gridWidth * gridHeight];
    for (int i = 0; i < gridWidth * gridHeight; i++)
        coverage[i] = 0;

    // Шаг 5. Для каждого входного прямоугольника прибавляем 1 в тех ячейках,
    // которые он покрывает. Для этого находим индексы границ, совпадающих с его краями.
    for (int r = 0; r < numRect; r++) {
        float rx1 = rectangles_arr[r].getCordLeftDown().X;
        float rx2 = rectangles_arr[r].getCordRightUp().X;
        float ry1 = rectangles_arr[r].getCordLeftDown().Y;
        float ry2 = rectangles_arr[r].getCordRightUp().Y;
        int xi1 = -1, xi2 = -1, yi1 = -1, yi2 = -1;
        for (int i = 0; i < distinctX; i++) {
            if (xBounds[i] == rx1) xi1 = i;
            if (xBounds[i] == rx2) xi2 = i;
        }
        for (int j = 0; j < distinctY; j++) {
            if (yBounds[j] == ry1) yi1 = j;
            if (yBounds[j] == ry2) yi2 = j;
        }
        if (xi1 == -1 || xi2 == -1 || yi1 == -1 || yi2 == -1)
            continue;
        // Для всех ячеек, попадающих в прямоугольник, увеличиваем счётчик.
        for (int i = xi1; i < xi2; i++) {
            for (int j = yi1; j < yi2; j++) {
                coverage[i + j * gridWidth]++;
            }
        }
    }

    // Шаг 6. Для каждой колонки определяем вертикальные сегменты ячеек,
    // где покрытие удовлетворяет условию (coverage >= k).
    // При этом фиксируем также значение покрытия (оно может быть разным).
    struct Segment {
        int start; // индекс строки начала сегмента
        int end;   // индекс строки конца (включительно)
        int cov;   // значение покрытия в ячейках сегмента
        bool used; // флаг, использовано ли уже при горизонтальном объединении
    };

    // Для каждой колонки выделяем массив сегментов.
    Segment** colSegments = new Segment * [gridWidth];
    int* segCount = new int[gridWidth];
    for (int i = 0; i < gridWidth; i++) {
        colSegments[i] = new Segment[gridHeight]; // максимум – по одной ячейке в сегменте
        segCount[i] = 0;
        int j = 0;
        while (j < gridHeight) {
            int cov = coverage[i + j * gridWidth];
            if (cov >= (int)k) {
                int start = j;
                int end = j;
                j++;
                // расширяем сегмент по вертикали, если следующие ячейки имеют то же значение покрытия
                while (j < gridHeight && coverage[i + j * gridWidth] == cov) {
                    end = j;
                    j++;
                }
                colSegments[i][segCount[i]].start = start;
                colSegments[i][segCount[i]].end = end;
                colSegments[i][segCount[i]].cov = cov;
                colSegments[i][segCount[i]].used = false;
                segCount[i]++;
            }
            else {
                j++;
            }
        }
    }

    // Шаг 7. Горизонтальное объединение.
    // Для каждой колонки и для каждого сегмента, который ещё не объединён,
    // пробуем расширить область вправо, если в следующей колонке существует сегмент,
    // точно совпадающий по вертикальному интервалу и по значению покрытия.
    std::cout << "Результирующие прямоугольники (формат: x1 y1 x2 y2):\n";
    for (int i = 0; i < gridWidth; i++) {
        for (int s = 0; s < segCount[i]; s++) {
            if (colSegments[i][s].used)
                continue;
            int segStart = colSegments[i][s].start;
            int segEnd = colSegments[i][s].end;
            int segCov = colSegments[i][s].cov;
            int leftCol = i;
            int rightCol = i;
            colSegments[i][s].used = true;
            // расширяем вправо
            for (int col = i + 1; col < gridWidth; col++) {
                bool found = false;
                for (int s2 = 0; s2 < segCount[col]; s2++) {
                    if (!colSegments[col][s2].used &&
                        colSegments[col][s2].start == segStart &&
                        colSegments[col][s2].end == segEnd &&
                        colSegments[col][s2].cov == segCov) {
                        found = true;
                        colSegments[col][s2].used = true;
                        break;
                    }
                }
                if (found)
                    rightCol = col;
                else
                    break;
            }
            // По полученным индексам восстанавливаем координаты:
            // По оси X: левая граница = xBounds[leftCol], правая = xBounds[rightCol+1].
            // По оси Y: нижняя = yBounds[segStart], верхняя = yBounds[segEnd+1].
            float rx1 = xBounds[leftCol];
            float rx2 = xBounds[rightCol + 1];
            float ry1 = yBounds[segStart];
            float ry2 = yBounds[segEnd + 1];
            std::cout << rx1 << " " << ry1 << " " << rx2 << " " << ry2 << "\n";
        }
    }

    // Шаг 8. Освобождаем динамическую память.
    for (int i = 0; i < gridWidth; i++) {
        delete[] colSegments[i];
    }
    delete[] colSegments;
    delete[] segCount;
    delete[] coverage;
    delete[] xBounds;
    delete[] yBounds;
}