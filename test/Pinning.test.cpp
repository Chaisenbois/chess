#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"


TEST(PinTest, piece_pinned_on_rank)
{
	BoardGame board;
	King king{ board, board[13], PieceColor::white };
	Queen queen{ board, board[29], PieceColor::white };
	Rock rock{ board, board[45], PieceColor::black };
	queen.compute_eligible_squares();
	rock.compute_eligible_squares();
	queen.filter_eligible_square_if_pinned();
	const auto& queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[21], &board[37], &board[45]})
	);
}


TEST(PinTest, piece_pinned_on_file)
{
	BoardGame board;
	King king{ board, board[8], PieceColor::white };
	Queen queen{ board, board[14], PieceColor::white };
	Rock rock{ board, board[15], PieceColor::black };
	queen.compute_eligible_squares();
	rock.compute_eligible_squares();
	queen.filter_eligible_square_if_pinned();
	const auto& queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[9], &board[10], &board[11], &board[12], &board[13], &board[15]})
	);
}


TEST(PinTest, piece_pinned_on_diagonal)
{
	BoardGame board;
	King king{ board, board[14], PieceColor::white };
	Queen queen{ board, board[28], PieceColor::white };
	Bishop bishop{ board, board[42], PieceColor::black };
	queen.compute_eligible_squares();
	bishop.compute_eligible_squares();
	queen.filter_eligible_square_if_pinned();
	const auto& queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[21], &board[35], &board[42] })
	);
}

TEST(PinTest, piece_pinned_on_anti_diagonal)
{
	BoardGame board;
	King king{ board, board[9], PieceColor::white };
	Queen queen{ board, board[27], PieceColor::white };
	Bishop bishop{ board, board[54], PieceColor::black };
	queen.compute_eligible_squares();
	bishop.compute_eligible_squares();
	queen.filter_eligible_square_if_pinned();
	const auto& queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 60);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[18], &board[36], &board[45], &board[54]})
	);
}

TEST(PinTest, not_pinned_if_friend_piece_between)
{
	BoardGame board;
	King king{ board, board[9], PieceColor::white };
	Pawn pawn{ board, board[18], PieceColor::white };
	Queen queen{ board, board[27], PieceColor::white };
	Bishop bishop{ board, board[54], PieceColor::black };
	queen.compute_eligible_squares();
	bishop.compute_eligible_squares();
	queen.filter_eligible_square_if_pinned();
	const auto& queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 41);
}


TEST(PinTest, not_pinned_if_enemy_piece_between)
{
	BoardGame board;
	King king{ board, board[9], PieceColor::white };
	Pawn pawn{ board, board[18], PieceColor::black };
	Queen queen{ board, board[27], PieceColor::white };
	Bishop bishop{ board, board[54], PieceColor::black };
	queen.compute_eligible_squares();
	bishop.compute_eligible_squares();
	queen.filter_eligible_square_if_pinned();
	const auto& queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 40);
}
