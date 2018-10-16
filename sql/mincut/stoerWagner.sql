/*PGR-GNU*****************************************************************
File: stoerWagner.sql

Generated with Template by:
Copyright (c) 2016 pgRouting developers
Mail: project@pgrouting.org

Function's developer:
Copyright (c) 2018 Aditya Pratap Singh
Mail: adityapratap.singh28@gmail.com

------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

********************************************************************PGR-GNU*/

CREATE OR REPLACE FUNCTION pgr_stoerWagner(
    edges_sql TEXT,             -- Edge sql

    OUT seq INTEGER,            -- Seq
    OUT edge BIGINT,            -- edges which divides the set of vertices into two.
    OUT cost FLOAT,             -- cost of edge
    OUT mincut FLOAT)           -- vertices of partition, min-cut weight of a undirected graph
RETURNS SETOF RECORD AS
'MODULE_PATHNAME', 'stoerWagner'
LANGUAGE c VOLATILE STRICT;