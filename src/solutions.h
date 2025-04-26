#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include "config.h"


class Solutions 
{
public:
    Solutions() = default;

    explicit Solutions(const std::vector<Board>& solutions) 
        : solutions_(solutions) {}
    
    void add(const Board& solution) 
    {
        solutions_.push_back(solution);
    }
    
    void add_all(const std::vector<Board>& solutions) 
    {
        solutions_.insert(solutions_.end(), solutions.begin(), solutions.end());
    }
    
    const Board& get(size_t index) const 
    {
        return solutions_.at(index);
    }
    
    const std::vector<Board>& all() const 
    {
        return solutions_;
    }
    
    size_t count() const 
    {
        return solutions_.size();
    }
    
    bool empty() const 
    {
        return solutions_.empty();
    }
    
    Solutions filter_symmetric() const 
    {
        Solutions unique_solutions;
        std::vector<Board> seen;
        
        for (const auto& sol : solutions_) 
        {
            if (!contains_rotation_or_reflection(seen, sol)) 
            {
                seen.push_back(sol);
                unique_solutions.add(sol);
            }
        }
        
        return unique_solutions;
    }
    
    std::array<int, BOARD_SIZE> queen_position_stats(int column) const 
    {
        std::array<int, BOARD_SIZE> stats{};
        for (const auto& sol : solutions_) 
        {
            stats[sol[column]]++;
        }
        return stats;
    }
    
    bool save_to_file(const std::string& filename) const 
    {
        std::ofstream file(filename);
        if (!file.is_open()) return false;
        
        for (const auto& sol : solutions_) 
        {
            for (int pos : sol) {
                file << pos << ' ';
            }
            file << '\n';
        }
        
        return true;
    }
    
    bool load_from_file(const std::string& filename) 
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        
        solutions_.clear();
        Board sol;
        
        while (file >> sol[0]) 
        {
            for (int i = 1; i < BOARD_SIZE; ++i) 
            {
                file >> sol[i];
            }
            solutions_.push_back(sol);
        }
        
        return true;
    }
    
    // The iterators for "range-based for"
    auto begin() const { return solutions_.begin(); }
    auto end() const { return solutions_.end(); }
    
private:
    std::vector<Board> solutions_;
    
    bool contains_rotation_or_reflection(const std::vector<Board>& seen, const Board& board) const 
    {
        auto rotations_and_reflections = generate_symmetries(board);        
        for (const auto& variant : rotations_and_reflections) 
        {
            if (std::find(seen.begin(), seen.end(), variant) != seen.end()) 
            {
                return true;
            }
        }

        return false;
    }
    
    std::vector<Board> generate_symmetries(const Board& board) const 
    {
        std::vector<Board> symmetries;
        
        // Original board
        symmetries.push_back(board);
        
        // Rotations & reflections
        Board rotated90, rotated180, rotated270;
        Board reflected, reflected90, reflected180, reflected270;
        
        for (int i = 0; i < BOARD_SIZE; ++i) 
        {
            rotated90[i] = BOARD_SIZE - 1 - board[i];
            rotated180[BOARD_SIZE - 1 - i] = BOARD_SIZE - 1 - board[i];
            rotated270[BOARD_SIZE - 1 - i] = board[i];
            
            reflected[i] = board[BOARD_SIZE - 1 - i];
            reflected90[i] = BOARD_SIZE - 1 - reflected[i];
            reflected180[BOARD_SIZE - 1 - i] = BOARD_SIZE - 1 - reflected[i];
            reflected270[BOARD_SIZE - 1 - i] = reflected[i];
        }
        
        symmetries.insert(symmetries.end(), {rotated90, rotated180, rotated270, 
                                           reflected, reflected90, reflected180, reflected270});
        
        return symmetries;
    }
};


#endif //SOLUTIONS_H