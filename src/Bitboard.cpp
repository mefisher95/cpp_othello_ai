#include "Bitboard.h"
#include <iostream>
#include <cmath>

Bitboard::Bitboard(uint64_t player0, uint64_t player1)
: player0_(player0), player1_(player1),
E_(uint64_t(0x8080808080808080)), W_(uint64_t(0x101010101010101)),
NE_(uint64_t(0x80808080808080FF)), NW_(uint64_t(0x1010101010101FF)),
SE_(uint64_t(0xFF80808080808080)), SW_(uint64_t(0xFF01010101010101))
{
    make_move(1, 27);
    make_move(0, 28);
    make_move(0, 35);
    make_move(1, 36);
}

Bitmap Bitboard::player0() const { return player0_; }
Bitmap Bitboard::player1() const { return player1_; }

int Bitboard::board_popcount() const { return (player0_ | player1_).pop_count(); }
int Bitboard::player0_popcount() const { return player0_.pop_count(); }
int Bitboard::player1_popcount() const { return player1_.pop_count(); }

void Bitboard::print(std::vector< DirTuple > possible_moves) const
{
    Bitmap candidates;

    for (int i = 0; i < possible_moves.size(); ++i)
    {
        std::cout << possible_moves[i][1] << std::endl;
        candidates = candidates |  (Bitmap(1)<< possible_moves[i][1]);
    }
    std::cout << "  A B C D E F G H" << std::endl;
    std::cout << " +-+-+-+-+-+-+-+-+" << std::endl;
    for (int i = 0; i < 64; ++i)
    {
        if (!i) std::cout << "0|";
        if (i > 0) std::cout << "|";
        if (i > 0 && !(i % 8)) std::cout << "\n +-+-+-+-+-+-+-+-+\n" << i / 8 << "|";
        if (player0()[i]) std::cout << "O";
        else if (player1()[i]) std::cout << "@";
        else if (candidates[i]) std::cout << "*";
        else std::cout << " ";
    }
    std::cout << "|\n +-+-+-+-+-+-+-+-+" << std::endl;
    std::cout << "  A B C D E F G H" << std::endl;
}

void Bitboard::make_move(const bool player, const int pos)
{
    if (pos < 0 || pos > 63) throw BitException(0, ("Invalid Position; position '" + std::to_string(pos) + "' outside valid range (0-63) (int pos)").c_str());
    if ((player0_ | player1_)[pos]) throw BitException(1, ("Invalid Position; position '" + std::to_string(pos) + "' already occupied (int pos)").c_str());
    switch (player)
    {
        case 0:
        player0_ = (player0_) | (Bitmap(1) << pos);
        return;

        case 1:
        player1_ = (player1_) | (Bitmap(1) << pos);
        return;
    }
}

void Bitboard::make_move(const bool current_player, const DirTuple & player_move)
{
    uint64_t pos = player_move[1];
    Bitmap empty_map(0);
    Bitmap original_move(Bitmap(1) << pos);
    Bitmap move = original_move;
    Bitmap captured_pieces = empty_map;
    Bitmap x;

    Bitmap player, opponent;
    if (current_player)
    {
        player = player1_;
        opponent = player0_;
    }
    else
    {
        player = player0_;
        opponent = player1_;
    }

    player = player | move;

    // North capture
    move = move >> n;
    for (int i = 0; i < n && !(move & opponent).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move >> n;
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }

    move = original_move;
    captured_pieces = empty_map;

    // South
    move = move << n;
    for (int i = 0; i < n && !(move & opponent).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move << n;
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }
    move = original_move;
    captured_pieces = empty_map;

    // East
    move = move << 1;
    x = E_;
    for (int i = 0; i < n && (!(move & opponent & ~(x)).is_empty()); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move << 1;
        x = x | (x << 1);
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }
    move = original_move;
    captured_pieces = empty_map;


    //West
    move = move >> 1;
    x = W_;
    for (int i = 0; i < 8 && !(move & opponent & (~x)).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move >> 1;
        x = x | (x >> 1);
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }
    move = original_move;
    captured_pieces = empty_map;

    // North East
    move = move >> n - 1;
    x = NE_;
    for (int i = 0; i < n && !(move & opponent & (~x)).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move >> n - 1;
        x = x | (x >> n - 1);
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }
    move = original_move;
    captured_pieces = empty_map;

    // North West
    move = move >> n + 1;
    x = NW_;
    for (int i = 0; i < n && !(move & opponent & (~x)).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move >> n + 1;
        x = x | (x >> n + 1);
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }
    move = original_move;
    captured_pieces = empty_map;

    // South East
    move = move << n + 1;
    x = SE_;
    for (int i = 0; i < n && !(move & opponent & (~x)).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move << n + 1;
        x = x | (x << n + 1);
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }
    move = original_move;
    captured_pieces = empty_map;

    // South West
    move = move << n - 1;
    x = SW_;
    for (int i = 0; i < n && !(move & opponent & (~x)).is_empty(); ++i)
    {
        captured_pieces = captured_pieces | (move & opponent);
        move = move << n - 1;
        x = x | (x << n - 1);
    }
    if (!(move & player).is_empty())
    {
        player = player | captured_pieces;
        opponent = opponent ^ captured_pieces;
    }


    // reasign back to players, may optomize with pointers
    if (current_player)
    {
        player1_ = player;
        player0_ = opponent;
    }
    else
    {
        player0_ = player;
        player1_ = opponent;
    }
}

std::vector< DirTuple > Bitboard::get_actions(const bool player_piece)
{
    std::vector< DirTuple > all_moves;
    Bitmap empty_map(0), moves(0), empty_positions(~(player0_ | player1_));

    //set players
    Bitmap player, opponent;
    if (player_piece)
    {
        player = player1();
        opponent = player0();
    }
    else
    {
        player = player0();
        opponent = player1();
    }


    // North
    moves = empty_map;
    Bitmap candidates(opponent & (player << 8));
    while (!candidates.is_empty())
    {
        moves = moves | empty_positions & (candidates << 8);
        candidates = opponent & (candidates << 8);
    }
    if (!moves.is_empty()) all_moves.push_back(DirTuple(N, moves));

    // South
    moves = empty_map;
    candidates = opponent & (player >> 8);
    while(!candidates.is_empty())
    {
        moves = moves | empty_positions & (candidates >> 8);
        candidates = opponent & (candidates >> 8);
    }
    if (!moves.is_empty()) all_moves.push_back(DirTuple(S, moves));

    // East
    moves = empty_map;
    candidates = opponent & (player >> 1);
    Bitmap x(E_);

    for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
    {
        x = x | (x >> uint64_t(1));
        moves = moves | empty_positions & (candidates >> uint64_t(1)) & ~(x);
        candidates = opponent & (candidates >> uint64_t(1));
    }
    if(!moves.is_empty()) all_moves.push_back(DirTuple(E, moves));

    // West
    moves = empty_map;
    candidates = opponent & (player << 1);
    x = W_;
    for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
    {
        x = x | (x << uint64_t(1));
        moves = moves | empty_positions & (candidates << uint64_t(1)) & ~(x);
        candidates = opponent & (candidates << uint64_t(1));
    }

    if(!moves.is_empty()) all_moves.push_back(DirTuple(W, moves));

    // North West
    moves = empty_map;
    candidates = opponent & (player << 9);
    x = NW_;

    for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
    {
        x = x | (x << uint64_t(9));
        moves = moves | empty_positions & (candidates << uint64_t(9)) & ~(x);
        candidates = opponent & (candidates << uint64_t(9));
    }

    if(!moves.is_empty()) all_moves.push_back(DirTuple(NW, moves));

    // South West
    moves = empty_map;
    candidates = opponent & (player >> 7);
    x = SW_;

    for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
    {
        x = x | (x >> uint64_t(7));
        moves = moves | empty_positions & (candidates >> uint64_t(7)) & ~(x);
        candidates = opponent & (candidates >> uint64_t(7));
    }

    if(!moves.is_empty()) all_moves.push_back(DirTuple(SW, moves));


    // North East
    moves = empty_map;
    candidates = opponent & (player << 7);
    x = NE_;

    for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
    {
        x = x | (x << uint64_t(7));
        moves = moves | empty_positions & (candidates << uint64_t(7)) & ~(x);
        candidates = opponent & (candidates << uint64_t(7));
    }
    if(!moves.is_empty()) all_moves.push_back(DirTuple(NE, moves));



    // South East
    moves = empty_map;
    candidates = opponent & (player >> 9);
    x = SE_;
    for (int i = 0; i < 8 && !candidates.is_empty(); ++i)
    {
        x = x | (x >> uint64_t(9));
        moves = moves | empty_positions & (candidates >> uint64_t(9)) & ~(x);
        candidates = opponent & (candidates >> uint64_t(9));
    }
    if(!moves.is_empty()) all_moves.push_back(DirTuple(SE, moves));

    std::vector< DirTuple > seperate_moves;

    for (int i = 0; i < all_moves.size(); ++i)
    {
        std::vector< int > moves_as_indicies = extract_moves(all_moves[i][1]);

        for (int k = 0; k < moves_as_indicies.size(); ++k)
        {
            if (should_add_index(seperate_moves, moves_as_indicies[k]))
            seperate_moves.push_back(DirTuple(direction(all_moves[i][0]), moves_as_indicies[k]));
        }
    }

    return seperate_moves;
}

std::vector< int > Bitboard::extract_moves(Bitmap move_as_map)
{
    std::vector< int > moves_as_indicies;
    int pos = 0;

    while(!move_as_map.is_empty())
    {
        if (move_as_map % 2) moves_as_indicies.push_back(pos);
        ++pos;
        move_as_map = move_as_map >> 1;
    }

    return moves_as_indicies;
}

bool Bitboard::should_add_index(std::vector< DirTuple > &seperate_moves, int index)
{
    for (int i = 0; i < seperate_moves.size(); ++i)
    {
        if (seperate_moves[i][1] == index) return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &cout, const Bitboard &bitboard)
{
    cout << bitboard.player0();
    cout << '\n';
    cout << bitboard.player1();
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const DirTuple &tuple)
{
    cout << "< "
         << tuple[0]
         << ", "
         << tuple[1]
         << " >";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, const std::vector< DirTuple > dt)
{
    cout << "[";
    for (int i = 0; i < dt.size(); ++i)
    {
        cout << dt[i];
        if (i < dt.size() - 1) cout << ", ";
    }
    cout << "]";
    return cout;
}
