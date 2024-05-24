#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

// 배열을 시각적으로 나타내는 함수
void drawArray(sf::RenderWindow& window, const std::vector<int>& array) {
    window.clear();
    float barWidth = window.getSize().x / static_cast<float>(array.size());
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 1, array[i]));
        bar.setPosition(i * barWidth, window.getSize().y - array[i]);
        bar.setFillColor(sf::Color::Green);
        window.draw(bar);
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 시각화를 위한 시간 지연
}

// 퀵소트 알고리즘 구현
void quickSort(std::vector<int>& array, int low, int high, sf::RenderWindow& window) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (array[j] <= pivot) {
                std::swap(array[++i], array[j]);
                drawArray(window, array); // 배열 상태 시각화
            }
        }
        std::swap(array[i + 1], array[high]);
        drawArray(window, array); // 배열 상태 시각화

        int pi = i + 1;
        quickSort(array, low, pi - 1, window);
        quickSort(array, pi + 1, high, window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "QuickSort Visualization");

    // 랜덤 배열 생성
    std::vector<int> array(100);
    for (int i = 0; i < array.size(); ++i) {
        array[i] = rand() % window.getSize().y;
    }

    // 퀵소트 알고리즘 실행
    quickSort(array, 0, array.size() - 1, window);

    // 정렬된 배열을 무한히 보여줌
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        drawArray(window, array);
    }

    return 0;
}
