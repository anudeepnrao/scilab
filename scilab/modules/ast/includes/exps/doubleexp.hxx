/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2007-2008 - DIGITEO - Bruno JOFRET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef AST_DOUBLEEXP_HXX
#define AST_DOUBLEEXP_HXX

#include "constexp.hxx"

#include "visitor.hxx"

namespace ast
{
/** \brief Abstract an Double Expression node.
**
** \b Example:  42.51 */
class DoubleExp : public ConstExp
{
public:
    DoubleExp (const Location& location, double value)
        : ConstExp (location),
          _value (value)
    {
    }

    DoubleExp (const Location& location, types::InternalType* value)
        : ConstExp (location),
          _value (0)
    {
        setConstant(value);
    }
    /** \brief Destroy an Double Expression node.
    **
    ** Delete size et init (exp) (see constructor). */
    virtual ~DoubleExp ()
    {
    }
    /** \} */

    virtual DoubleExp* clone()
    {
        DoubleExp* cloned = new DoubleExp(getLocation(), getValue());
        cloned->setVerbose(isVerbose());
        return cloned;
    }
    /** \name Visitors entry point.
    ** \{ */
public:
    /** \brief Accept a const visitor \a v. */
    virtual void accept (Visitor& v)
    {
        v.visit (*this);
    }
    /** \brief Accept a non-const visitor \a v. */
    virtual void accept (ConstVisitor& v) const
    {
        v.visit (*this);
    }
    /** \} */


    /** \name Accessors.
    ** \{ */
public:
    /** \brief Return the value */
    double getValue() const
    {
        return _value;
    }
    /** \} */

    virtual ExpType getType()
    {
        return DOUBLEEXP;
    }
    inline bool isDoubleExp() const
    {
        return true;
    }

protected:
    double _value;
};

} // namespace ast
#endif