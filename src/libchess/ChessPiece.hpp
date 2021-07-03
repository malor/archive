#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__

#include <iosfwd>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Visitor.hpp"
#include "common.hpp"

class ChessBoard;
class ChessPiece;

typedef boost::shared_ptr<ChessPiece> (*CreateChessPiece)();


class DLL_PUBLIC ChessPiece
{
public:
    enum Color {BLACK, WHITE};

    ChessPiece(Color col);

    virtual ~ChessPiece() { }

    Color color() const;
    void setColor(Color col);
    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const = 0;

    static std::map<char, CreateChessPiece> creators;
    static bool registerCreator(char label, CreateChessPiece func);
    static boost::shared_ptr<ChessPiece> load(std::istream& is);

    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor) = 0;

protected:
    Color _color;
};

#endif /* __CHESSPIECE_H__ */
