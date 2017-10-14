//
//  hilbert_curve.hpp
//
//  Created by ISHII 2bit on 2017/10/12.
//

#pragma once

#ifndef hilbert_curve_h
#define hilbert_curve_h

#include <cstddef>
#include <vector>

namespace bbb {
    struct hilbert_curve {
        struct coordinate {
            coordinate(long x, long y) : x(x), y(y) {}
            coordinate() : coordinate(0l, 0l) {};
            inline coordinate operator+(const coordinate &c) const { return {x + c.x, y + c.y}; };
            inline coordinate operator-(const coordinate &c) const { return {x - c.x, y - c.y}; };
            
            long x;
            long y;
        };
        
        using iterator = std::vector<coordinate>::iterator;
        using const_iterator = std::vector<coordinate>::const_iterator;
        using reverse_iterator = std::vector<coordinate>::reverse_iterator;
        using const_reverse_iterator = std::vector<coordinate>::const_reverse_iterator;
        
        hilbert_curve() = default;
        hilbert_curve(std::size_t order)
            : order_(order)
            , width_(1 << order)
            , coordinates(width_ * width_)
            , indices(width_ * width_)
            , coord(-1l, 0l)
            , index(0)
        {
            step(0);
            hilbert(0, 1, order_);
        }
        
        hilbert_curve(const hilbert_curve &) = default;
        hilbert_curve(hilbert_curve &&) = default;
        
        hilbert_curve &operator=(const hilbert_curve &) = default;
        hilbert_curve &operator=(hilbert_curve &&) = default;
        
        inline std::size_t size() const { return coordinates.size(); }
        inline std::size_t width() const { return width_; }
        inline std::size_t order() const { return order_; }
        
        inline operator const std::vector<coordinate> &() const & { return coordinates; }
        inline operator const std::vector<coordinate> &() && { return std::move(coordinates); }
        inline operator const std::vector<std::size_t> &() const & { return indices; }
        inline operator const std::vector<std::size_t> &() && { return std::move(indices); }

        inline coordinate operator[](std::size_t id) const { return coordinates[id]; }
        inline coordinate coordinate_at(std::size_t id) { return coordinates[id]; }
        inline std::size_t index_at(std::size_t x, std::size_t y) const { return indices[x + y * width()]; }
        
        inline const_iterator begin() const { return coordinates.cbegin(); }
        inline const_iterator cbegin() const { return coordinates.cbegin(); }
        
        inline const_iterator end() const { return coordinates.cend(); }
        inline const_iterator cend() const { return coordinates.cend(); }
        
        inline const_reverse_iterator rbegin() const { return coordinates.crbegin(); }
        inline const_reverse_iterator crbegin() const { return coordinates.crbegin(); }
        
        inline const_reverse_iterator rend() const { return coordinates.crend(); }
        inline const_reverse_iterator crend() const { return coordinates.crend(); }
        
    private:
        inline void step(int direction) {
            switch(direction & 3) {
                case 0: coord.x++; break;
                case 1: coord.y++; break;
                case 2: coord.x--; break;
                case 3: coord.y--; break;
            }
            
            coordinates[index] = coord;
            indices[coord.x + coord.y * width()] = index;
            
            index++;
        }
        
        void hilbert(int direction, int rotation, std::size_t order) {
            if(order == 0) return;
            --order;
            
            direction += rotation;
            
            hilbert(direction, -rotation, order);
            step(direction);
            
            direction -= rotation;
            
            hilbert(direction, rotation, order);
            step(direction);
            hilbert(direction, rotation, order);
            
            direction -= rotation;
            
            step(direction);
            hilbert(direction, -rotation, order);
        }
        
        std::size_t order_;
        std::size_t width_;
        std::vector<coordinate> coordinates;
        std::vector<std::size_t> indices;
        
        coordinate coord;
        std::size_t index;
    };
};

#endif /* hilbert_curve_h */
