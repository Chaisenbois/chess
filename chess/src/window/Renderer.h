#pragma once
#include <SDL2/SDL.h>
#include <tuple>
#include "../game/Piece.h"
#include "Types.h"


class Renderer
{
public:
	Renderer(SDL_Window& window, const WindowSize window_size,
		const CaseColor primary_color, const CaseColor secondary_color): renderer_( SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ),
		primary_color_(primary_color), secondary_color_(secondary_color),
		window_size_(window_size) {}
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void render_board() const noexcept;
	std::tuple<int, int> get_case_dimensions() const noexcept;
	void render_selection(const Asset& asset) const noexcept;
	void render_legal_squares(const Asset& asset) const noexcept;
	void clear_selection(const Asset& asset) const noexcept;
	void clear_legal_squares(const Asset& asset) const noexcept;
	void render_square(const Square& square) const noexcept;
	void render_square(const Square& square, CaseColor color) const noexcept;
	void render_asset(const Asset& asset) const noexcept;
	void update_screen() const noexcept;
	void add_asset(Piece& piece, SDL_Surface& surface)  noexcept;
	std::vector<Asset>& get_assets() noexcept { return this->assets_; }
	const Asset* get_asset_of_coordinates(int x, int y) const noexcept;
	void render_assets() const noexcept;
private:
	SDL_Renderer* renderer_;
	CaseColor primary_color_;
	CaseColor secondary_color_;
	WindowSize window_size_;
	std::vector<Asset> assets_;

	const Asset* get_asset_of_piece(const Piece& piece) const  noexcept;
	const CaseColor& get_square_case_color(const Square& square) const noexcept;
	SDL_Rect get_rect_of_square(const Square& square) const noexcept;
};
