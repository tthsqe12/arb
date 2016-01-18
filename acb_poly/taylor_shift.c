/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2016 Fredrik Johansson

******************************************************************************/

#include "acb_poly.h"

void
_acb_poly_taylor_shift(acb_ptr poly, const acb_t c, slong n, slong prec)
{
    if (n <= 30 || (n <= 1000 && acb_bits(c) == 1 && n < 30 + 3 * sqrt(prec))
            || (n <= 100 && acb_bits(c) < 0.01 * prec))
        _acb_poly_taylor_shift_horner(poly, c, n, prec);
    else
        _acb_poly_taylor_shift_divconquer(poly, c, n, prec);
}

void
acb_poly_taylor_shift(acb_poly_t g, const acb_poly_t f,
    const acb_t c, slong prec)
{
    if (f != g)
        acb_poly_set_round(g, f, prec);

    _acb_poly_taylor_shift(g->coeffs, c, g->length, prec);
}

