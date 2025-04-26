#ifndef CHESSVISUALIZER_H
#define CHESSVISUALIZER_H

#include <SFML/Graphics.hpp>
#include "config.h"


class ChessVisualizer 
{
    public:
        ChessVisualizer() 
        {
            if (!queen_texture_.loadFromFile("queen.png")) 
            {
                std::cerr << "Failed to load queen texture. Using fallback shape.\n";
                use_texture_ = false;
            } else {
                queen_sprite_.setTexture(queen_texture_);
                float scale = CELL_SIZE * 0.8f / queen_texture_.getSize().x;
                queen_sprite_.setScale(scale, scale);
                use_texture_ = true;
            }
            
            if (!font_.loadFromFile("arial.ttf")) 
            {
                std::cerr << "Failed to load font. Text will not be displayed.\n";
            }
        }
        
        void draw(sf::RenderWindow& window, const Board& board, size_t current, size_t total) 
        {
            draw_board(window);
            draw_queens(window, board);
            draw_info(window, current, total);
        }
        
    private:
        sf::Texture queen_texture_;
        sf::Sprite queen_sprite_;
        sf::Font font_;
        bool use_texture_ = false;
        
        const sf::Color light_color_ = sf::Color(240, 217, 181);
        const sf::Color dark_color_ = sf::Color(181, 136, 99);
        
        void draw_board(sf::RenderWindow& window) 
        {
            for (int row = 0; row < BOARD_SIZE; ++row) 
            {
                for (int col = 0; col < BOARD_SIZE; ++col) 
                {
                    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setPosition(col * CELL_SIZE, row * CELL_SIZE);
                    cell.setFillColor((row + col) % 2 == 0 ? light_color_ : dark_color_);
                    window.draw(cell);
                }
            }
        }
        
        void draw_queens(sf::RenderWindow& window, const Board& board) 
        {
            if (use_texture_) 
            {
                for (int col = 0; col < BOARD_SIZE; ++col) 
                {
                    int row = board[col];
                    queen_sprite_.setPosition(
                        col * CELL_SIZE + (CELL_SIZE - queen_sprite_.getGlobalBounds().width) / 2,
                        row * CELL_SIZE + (CELL_SIZE - queen_sprite_.getGlobalBounds().height) / 2
                    );
                    window.draw(queen_sprite_);
                }
            } else {
                // Fallback - draw circles instead of textures
                float radius = CELL_SIZE * 0.4f;
                for (int col = 0; col < BOARD_SIZE; ++col) 
                {
                    int row = board[col];
                    sf::CircleShape queen(radius);
                    queen.setPosition(
                        col * CELL_SIZE + (CELL_SIZE - radius * 2) / 2,
                        row * CELL_SIZE + (CELL_SIZE - radius * 2) / 2
                    );
                    queen.setFillColor(sf::Color::Black);
                    window.draw(queen);
                }
            }
        }
        
        void draw_info(sf::RenderWindow& window, size_t current, size_t total) 
        {
            if (font_.getInfo().family.empty()) return;
            
            sf::Text info_text;
            info_text.setFont(font_);
            info_text.setString("Solution: " + std::to_string(current + 1) + "/" + std::to_string(total));
            info_text.setCharacterSize(24);
            info_text.setFillColor(sf::Color::Black);
            info_text.setPosition(10, 10);
            window.draw(info_text);
            
            // Additional information about the positions of queens
            std::string positions = "Positions: ";
            for (int pos : Board{}) 
            {
                positions += std::to_string(pos) + " ";
            }
            
            sf::Text pos_text;
            pos_text.setFont(font_);
            pos_text.setString(positions);
            pos_text.setCharacterSize(18);
            pos_text.setFillColor(sf::Color::Black);
            pos_text.setPosition(10, WINDOW_SIZE - 30);
            window.draw(pos_text);
        }
    };


#endif //CHESSVISUALIZER_H