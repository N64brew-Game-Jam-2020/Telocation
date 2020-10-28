package main

type MaterialType int

const (
	LowerFloor MaterialType = 0
	UpperFloor MaterialType = 1
	BarrierTop MaterialType = 2
	Wall       MaterialType = 3
	Underhang  MaterialType = 4
)

var AllMaterials = []MaterialType{
	LowerFloor,
	UpperFloor,
	BarrierTop,
	Wall,
	Underhang,
}

type LevelBlockFace struct {
	Mesh     *Mesh
	Material MaterialType
}

type LevelBlock struct {
	IsSolid bool
	Left    *LevelBlockFace
	Right   *LevelBlockFace
	Front   *LevelBlockFace
	Back    *LevelBlockFace
	Top     *LevelBlockFace
}

type LevelTile struct {
	Blocks [3]*LevelBlock
}

type LevelTileSet struct {
	Tiles map[string]*LevelTile
}

type LevelTileSlot struct {
	Tile     *LevelTile
	Rotation int
}

type LevelGrid struct {
	Tiles [][]LevelTileSlot
}

func (tile *LevelTile) IsSolidAtHeight(height int) bool {
	return height >= 0 && height < 3 && tile.Blocks[height] != nil && tile.Blocks[height].IsSolid
}

func (level *LevelGrid) IsSolid(x, y, height int) bool {
	if x < 0 || y < 0 || x >= len(level.Tiles) {
		return false
	}

	var row = level.Tiles[x]

	if y >= len(row) {
		return false
	}

	var cell = row[y]

	if cell.Tile == nil {
		return false
	}

	return cell.Tile.IsSolidAtHeight(height)
}