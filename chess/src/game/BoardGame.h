#pragma once
#include <vector>
#include <memory>
#include "../Common.h"
#include "Square.h"
#include "PieceColor.h"


class CHESS_API  BoardGame
{
	using colors_type = std::array<std::unique_ptr<PieceColor>, 2>;
public:
	BoardGame();
	BoardGame(const BoardGame&) = delete;
	BoardGame(BoardGame&&) = delete;
	BoardGame& operator=(const BoardGame&) = delete;
	BoardGame& operator=(BoardGame&&) = delete;
	Square& operator[](const int8_t i) noexcept { return this->squares_[i]; }
	~BoardGame() = default;
	void init_game() const noexcept ;
	bool has_square_value(const int8_t value) const noexcept { return value >= 0 && value < squares_.size(); }
	PieceColor& get_color(const int8_t i) const  noexcept { return *this->colors_[i]; }
	const colors_type& get_colors() const  noexcept { return this->colors_; }
	PieceColor& get_turn() const noexcept;
	void set_turn(int8_t i) noexcept { this->turn_ = i; }
	void next_turn() noexcept;
private:
	void compute_legal_squares() const noexcept;
	std::vector<Square> squares_;
	colors_type colors_  { std::make_unique<WhiteColor>(*this), std::make_unique<BlackColor>(*this) };
	int8_t turn_ = 0;
};

