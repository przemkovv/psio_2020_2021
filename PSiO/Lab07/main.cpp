
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Moja n-ta gra Cyberpunk 2077");

    // create some shapes
    sf::CircleShape circle(100.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    /*
     * FPS = frames per second
     * 1s = 1000ms
     * 60 FPS ~ 1 frame bedzie trwala w przyblizeniu 16.66ms
     * 20 FPS ~ 1 ramka trwa 50ms
     */
    // run the program as long as the window is open

    auto startFrame = std::chrono::steady_clock::now();
    const auto counter_init = 10;
    auto counter = 0;

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        /*
         * EVENT QUEUE = {}
         *
         * 1. User: klika na srodku okna
         * 2. Windows: dodaje do EVENT QUEUE  zdarzenie klikniecia
         *
         * EVENT QUEUE = { click(50, 50) }
         * 3. User: klika na srodku okna
         * 4. Windows: dodaje do EVENT QUEUE  zdarzenie klikniecia
         * EVENT QUEUE = { click(50, 50),
         * 				   click(100, 50) }
         *
         * 5. App: pobiera zdarzenie z kolejki event = CLICK(50, 50)
         * EVENT QUEUE = { click(100, 50) }
         *
         * 6. App: obsluga event
         *
         * 7. App: pobiera zdarzenie z kolejki event = CLICK(100, 50)
         * EVENT QUEUE = { }
         *
         * 6. App: obsluga event
         *
         */


        std::array<bool, sf::Keyboard::KeyCount> keyStatus {};
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                keyStatus[event.key.code] = true;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
                        && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
                    triangle.move(-10, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
                        && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
                   /*
                    for (int iteratio = 0; i<10; ++iteration) {
                        triangle.move(-3, 0);
                        if (checkCollision()) {
                        }
                    }
                    */

                }
                if (event.key.code ==  sf::Keyboard::Key::S ) {
                    triangle.move(10, 0);
                }

                switch (event.key.code) {
                    case sf::Keyboard::Key::Q: {
//                    	if (keyStatus[sf::Keyboard::E] == true ) {

//                        }
                        break;
                    }
                    case sf::Keyboard::Key::E: {

                        break;
                    }
                default: break;

                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    window.close();
                }

            }
            if (event.type == sf::Event::KeyReleased) {
                keyStatus[event.key.code] = false;
            }

        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(10ms);
        }

        // end the current frame
        window.display();

        auto endFrame = std::chrono::steady_clock::now();
        auto durationFrame = endFrame - startFrame;
        if (counter++ > counter_init)
        {
            using namespace std::chrono;
            auto x = 1'000'000;
            /*
             * 10 / 5 = 2
             * 15 / 5 = 3
             * 5 / 5 = 1
             * 2 / 5 = 0
             * 1 /  5 = 0
             * 2.0f / 5 = 0.4f
             * 1.0f / 5 = 0.2f
             */
            std::cout << "Frame time: "  << duration_cast<microseconds>(durationFrame).count() << ' ';
            std::cout << "FPS: "  << 1'000'000.0f / duration_cast<microseconds>(durationFrame).count() << '\n';
            counter= 0;
        }
        startFrame = endFrame;
    }

    return 0;
}
