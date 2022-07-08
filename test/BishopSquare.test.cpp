#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(BishopSquareAvailable, all_square_free)
{
	BoardGame board;
	const Bishop bishop{ board, board[11], PieceColor::white };
	const auto bishop_eligible_squares = bishop.eligible_squares();
	EXPECT_THAT(bishop_eligible_squares, WhenSorted(ElementsAre(
		&board[2], &board[4], &board[18], &board[20], &board[25], &board[29],
		&board[32], &board[38], &board[47])));
}


TEST(BishopSquareAvailable, diagonal_square_taken)
{
	BoardGame board;
	const MockPiece p1{board, board[25], PieceColor::white};
	const MockPiece p2{board, board[38], PieceColor::white};
	const MockPiece p3{board, board[2], PieceColor::black};
	const Bishop bishop{ board, board[11], PieceColor::white };
	const auto bishop_eligible_squares = bishop.eligible_squares();
	EXPECT_THAT(bishop_eligible_squares, WhenSorted(ElementsAre(
		&board[2], &board[4], &board[18], &board[20], &board[29]
	 )));
}
