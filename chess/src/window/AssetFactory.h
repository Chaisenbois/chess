#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../game/Piece.h"
#include "../game/PieceColor.h"
#include "Application.h"


class PieceAssetFactory final: public PieceVisitor
{
public:
	static constexpr int8_t NB_SURFACES = 6;
	using surfaces_type = std::array<SDL_Surface*, NB_SURFACES>;
	PieceAssetFactory(Application& app, const std::array<std::string,NB_SURFACES >& sprite_names);
	PieceAssetFactory(const PieceAssetFactory&) = delete;
	PieceAssetFactory(PieceAssetFactory&&) = delete;
	PieceAssetFactory& operator=(const PieceAssetFactory&) = delete;
	PieceAssetFactory& operator=(PieceAssetFactory&&) = delete;
	void create_asset(Piece& piece, SDL_Surface* surface) const noexcept;
	~PieceAssetFactory() override;
	void visit(Bishop& piece) const override
	{
		this->create_asset(piece, this->surfaces_[2]);
	}
	void visit(King& piece) const override
	{
		this->create_asset(piece, this->surfaces_[0]);
	}
	void visit(Knight& piece) const override
	{
		this->create_asset(piece, this->surfaces_[3]);
	}
	void visit(Pawn& piece) const override
	{
		this->create_asset(piece, this->surfaces_[4]);
	}
	void visit(Queen& piece) const override
	{
		this->create_asset(piece, this->surfaces_[1]);
	}
	void visit(Rock& piece) const override
	{
		this->create_asset(piece, this->surfaces_[5]);
	}
protected:
	Application& app_;
	surfaces_type surfaces_;
};

class AssetFactory final: public ColorVisitor
{
public:
	AssetFactory(Application& app): app_(app) {}
	void create_piece_assets(const std::array<std::string, PieceAssetFactory::NB_SURFACES>& sprite_names,PieceColor& color) const noexcept;
	void visit(BlackColor& color) const override;
	void visit(WhiteColor& color) const override;
private:
	Application& app_;
};

