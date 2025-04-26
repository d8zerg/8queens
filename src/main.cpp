#include <algorithm>
#include "queenssolver.h"
#include "chessvisualizer.h"


int main() 
{
    QueensSolver solver;
    ChessVisualizer visualizer;
    
    // Search all solutions
    Solutions all_solutions = solver.find_all_solutions();
    std::cout << "Found " << all_solutions.count() << " solutions\n";
    
    // Search for unique solutions (without taking into account rotations and reflections)
    Solutions unique_solutions = solver.find_unique_solutions();
    std::cout << "Found " << unique_solutions.count() << " unique solutions\n";
    
    // Saving to file all solutions
    if (all_solutions.save_to_file("all_solutions.txt")) 
    {
        std::cout << "Saved all solutions to file\n";
    }
    
    // Create window with SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "8 Queens Visualizer");
    window.setFramerateLimit(60);
    
    size_t current_solution = 0;
    const bool show_unique_only = false;
    const Solutions& display_solutions = show_unique_only ? unique_solutions : all_solutions;
    
    // Main loop
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed) 
            {
                // Switching between all unique solutions
                switch (event.key.code) 
                {
                    case sf::Keyboard::Right:
                        current_solution = (current_solution + 1) % display_solutions.count();
                        break;
                    case sf::Keyboard::Left:
                        current_solution = (current_solution - 1 + display_solutions.count()) % display_solutions.count();
                        break;
                    case sf::Keyboard::U:                        
                        current_solution = 0;
                        const_cast<bool&>(show_unique_only) = !show_unique_only;
                        const_cast<Solutions&>(display_solutions) = show_unique_only ? unique_solutions : all_solutions;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
                
                // Output about the current solution
                std::cout << "Solution " << current_solution + 1 << "/" << display_solutions.count() << "\n";
                const auto& board = display_solutions.get(current_solution);
                for (int pos : board) std::cout << pos << " ";
                std::cout << "\n";
            }
        }
        
        // Draw window
        window.clear(sf::Color::White);
        visualizer.draw(window, display_solutions.get(current_solution), current_solution, display_solutions.count());
        window.display();
    }
    
    return 0;
}