
#pragma warning( disable : 4996 ) 


#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"

using namespace std;

struct _Heros
{
	int xMin, xMax, yMin, yMax, width;
	string texture =
		"[RRR  ]"
		"[RRWR ]"
		"[RRR  ]"
		"[YY   ]"
		"[YYY  ]"
		"[YY YG]"
		"[GG   ]"
		"[CC   ]"
		"[CC   ]"
		"[C C  ]"
		"[C C  ]";

	V2 Size;
	int IdTex;
	V2 Pos = V2(45, 45);
	bool hasKey = false;
	bool hasPistolet = false;
	bool nbBalles = 0;
	bool nbVie = 3;
	bool getNbVie() { return nbVie; }
	void setNbVie() { nbVie = nbVie-1; }
	bool getHasKey() { return hasKey; }
	void setHasKey() { hasKey = true;}

};

struct _Momie
{
	
	string texture =
		"[    O    ]"
		"[  BBOBB  ]"
		"[ BBOOOB  ]"
		"[BBBOOOBBB]"
		"[OOOWWWOOO]"
		"[BBWKWKWBB]"
		"[OOWWWWWOO]"
		"[BBWWRWWBB]"
		"[BGGWKWGGB]"
		"[BWGGKGGWB]"
		"[ WWGKGWW ]"
		"[ WWWGWWW ]"
		"[ WWWWWWW ]"
		"[ BWWWWWB ]"
		"[ WBBBBBW ]"
		"[  YYBYY  ]";
	V2 Size;
	int IdTex;
	//V2 Pos = V2(230, 250);
	V2 Pos;
	V2 Dir;
	_Momie(V2 _Pos) { Pos = _Pos; Dir =V2(1,0); }
	V2 getMomieDir() { return Dir; }
	void setMomieDir(V2 _Dir) { Dir = _Dir; }
};

struct _Key
{
	string texture =
		"[                   ]"
		"[  W R         WWRW ]"
		"[  W W        W    W]"
		"[WRWWWWWRWWWWWW    W]"
		"[             W    R]"
		"[              WWWW ]";


	V2 Size;
	int IdTex;
	V2 Pos = V2(440, 450);
};

struct _Chest
{
	string texture =
		"[   WWWWWWWWWWWWWW   ]"
		"[ WGGGGWWWWWWWWWWWWW ]"
		"[WG   GWW    WWW   WW]"
		"[WGRRGGW  YY  WWWRRWW]"
		"[WWRRWWWW    WWWWRRWW]"
		"[ WWWWWWWWWWWWWWWWWW ]";

	V2 Size;
	int IdTex;
	V2 Pos = V2(405, 50);

};

struct Rectangle
{
	int xMin, xMax, yMin, yMax;
	Rectangle(int _xMin, int _yMin, int _xMax, int _yMax) { xMin = _xMin, xMax = _xMax, yMin = _yMin, yMax = _yMax; }
};
struct GameData
{

	string Map =
		"MMMMMMMMMMMMMMM"
		"M M           M"
		"M M M MMM MMM M"
		"M   M       M M"
		"MMM M M MMM M M"
		"M   M M     M M"
		"M MMM MMM MMMMM"
		"M   M  M      M"
		"M M M  M M MM M"
		"M M M  M M M  M"
		"M M M MM M MMMM"
		"M M M    M    M"
		"M M M MMMMMMM M"
		"M M      M    M"
		"MMMMMMMMMMMMMMM";

	// indique la présence d'un mur à la case (x,y)
	bool Mur(int x, int y) { return Map[(15 - y - 1) * 15 + x] == 'M'; }

	int Lpix = 40;  // largeur en pixels des cases du labyrinthe

	_Heros Heros;   // data du héros


	_Key   Key;
	_Chest Chest;
	_Momie MomieListe[3] = {_Momie(V2(230, 250)), _Momie(V2(130, 420)), _Momie(V2(370,470)) };

	GameData() {}

};


GameData G;

bool InterRectRect(Rectangle R1, Rectangle R2)
{
	if (R1.yMax < R2.yMin) { return false; }
	if (R1.yMin > R2.yMax) { return false; }
	if (R1.xMin > R2.xMax) { return false; }
	if (R1.xMax < R2.xMin) { return false; }
	return true;
};

void render()
{
	G2D::ClearScreen(Color::Black);

	for (int x = 0; x < 15; x++)
		for (int y = 0; y < 15; y++)
		{
			int xx = x * G.Lpix;
			int yy = y * G.Lpix;
			if (G.Mur(x, y))
				G2D::DrawRectangle(V2(xx, yy), V2(G.Lpix, G.Lpix), Color::Blue, true);
		}

	// affichage du héro avec boite englobante et zoom x 2
	G2D::DrawRectangle(G.Heros.Pos, G.Heros.Size, Color::Red);
	G2D::DrawRectWithTexture(G.Heros.IdTex, G.Heros.Pos, G.Heros.Size);

	
	// affichage de la clef
	if (G.Heros.getHasKey() == false)
	{
		G2D::DrawRectWithTexture(G.Key.IdTex, G.Key.Pos, G.Key.Size);
	}

	// affichage du Chest 
	G2D::DrawRectWithTexture(G.Chest.IdTex, G.Chest.Pos, G.Chest.Size);

	// affichage d'une Momie
	for (int i = 0; i < 3; i = i + 1)
	{
		G2D::DrawRectWithTexture(G.MomieListe[i].IdTex, G.MomieListe[i].Pos, G.MomieListe[i].Size);

	}
	G2D::Show();
}
void murCollision()
{
	bool tapeUnCoin = (G.Mur(G.Heros.Pos.x / 40, G.Heros.Pos.y / 40)) || (G.Mur((G.Heros.Pos.x + G.Heros.Size.x) / 40, (G.Heros.Pos.y + G.Heros.Size.y) / 40)) || (G.Mur((G.Heros.Pos.x) / 40, (G.Heros.Pos.y + G.Heros.Size.y) / 40)) || (G.Mur((G.Heros.Pos.x + G.Heros.Size.x) / 40, (G.Heros.Pos.y) / 40));


	if (tapeUnCoin) {
		if (G2D::IsKeyPressed(Key::LEFT))  G.Heros.Pos.x++;
		if (G2D::IsKeyPressed(Key::RIGHT)) G.Heros.Pos.x--;
		if (G2D::IsKeyPressed(Key::UP))    G.Heros.Pos.y--;
		if (G2D::IsKeyPressed(Key::DOWN))  G.Heros.Pos.y++;
	}
};
void takeKey(Rectangle rectHero)
{
	Rectangle rectKey = Rectangle(G.Key.Pos.x, G.Key.Pos.y, G.Key.Pos.x + G.Key.Size.x, G.Key.Pos.y + G.Key.Size.y);
	if (InterRectRect(rectHero, rectKey))
	{
		G.Heros.setHasKey();
	}
}
void collision(Rectangle rectHero, Rectangle rectMomie)
{
	if (InterRectRect(rectHero, rectMomie))
	{
		G.Heros.Pos = V2(45, 45);
		G.Heros.setNbVie();
		if (G.Heros.getNbVie() == 0)
		{
			cout<<"VousetesAChier, DEfaite";
		}
	}
};

void coffreFin(Rectangle rectHero)
{
	Rectangle rectChest = Rectangle(G.Chest.Pos.x, G.Chest.Pos.y, G.Chest.Pos.x + G.Chest.Size.x, G.Chest.Pos.y + G.Chest.Size.y);
	if (InterRectRect(rectHero, rectChest))
	{
		if (G.Heros.getHasKey())
		{
			cout<<"FInDUJEUBITCH()";
		}
	}
}


void collision(_Heros& heros)
{
	Rectangle rectHero = Rectangle(G.Heros.Pos.x, G.Heros.Pos.y, G.Heros.Pos.x + G.Heros.Size.x, G.Heros.Pos.y + G.Heros.Size.y);
	// ? héros/mur
	murCollision();
	// ? héros/clé
	if (G.Heros.getHasKey() == false)
	{
		takeKey(rectHero);
	}
	// ? héros/momies
	for (int i = 0; i < 3; i++)
		{
			Rectangle rectMomie = Rectangle(G.MomieListe[i].Pos.x, G.MomieListe[i].Pos.y, G.MomieListe[i].Pos.x + G.MomieListe[i].Size.x, G.MomieListe[i].Pos.y + G.MomieListe[i].Size.y);
			collision(rectHero,rectMomie);
		}
	// ? héros/coffre
	coffreFin(rectHero);
}



//void momieCollision()
//{	
//	Rectangle rectHero = Rectangle(G.Heros.Pos.x, G.Heros.Pos.y, G.Heros.Pos.x + G.Heros.Size.x, G.Heros.Pos.y + G.Heros.Size.y);
//	for (int i = 0; i < 3; i++)
//	{
//		Rectangle rectMomie = Rectangle(G.MomieListe[i].Pos.x, G.MomieListe[i].Pos.y, G.MomieListe[i].Pos.x + G.MomieListe[i].Size.x, G.MomieListe[i].Pos.y + G.MomieListe[i].Size.y);
//		if (InterRectRect(rectHero, rectMomie))
//		{
//			if (G2D::IsKeyPressed(Key::LEFT))  G.Heros.Pos.x++;
//			if (G2D::IsKeyPressed(Key::RIGHT)) G.Heros.Pos.x--;
//			if (G2D::IsKeyPressed(Key::UP))    G.Heros.Pos.y--;
//			if (G2D::IsKeyPressed(Key::DOWN))  G.Heros.Pos.y++;
//		}
//	}	
//};
void DeplacementMomies(_Momie  & momie)
{
	V2 newPos = momie.Pos + momie.Dir;

	if (!((G.Mur(newPos.x / 40, newPos.y / 40)) || (G.Mur((newPos.x + momie.Size.x) / 40, (newPos.y + momie.Size.y) / 40)) || (G.Mur((newPos.x) / 40, (newPos.y + momie.Size.y) / 40)) || (G.Mur((newPos.x + momie.Size.x) / 40, (newPos.y) / 40))))
	{
		momie.Pos = newPos;
	}
	else
	{
		V2 Dir[4] = { V2(0,1), V2(1,0), V2(0,-1), V2(-1,0) };
		int rd = rand()%4;
		momie.Dir = Dir[rd];
	}
		
	

}




void Logic()
{
	if (G2D::IsKeyPressed(Key::LEFT))  G.Heros.Pos.x--;
	if (G2D::IsKeyPressed(Key::RIGHT)) G.Heros.Pos.x++;
	if (G2D::IsKeyPressed(Key::UP))    G.Heros.Pos.y++;
	if (G2D::IsKeyPressed(Key::DOWN))  G.Heros.Pos.y--;
	//murCollision();

	Rectangle rectChest = Rectangle(G.Chest.Pos.x, G.Chest.Pos.y, G.Chest.Pos.x + G.Chest.Size.x, G.Chest.Pos.y + G.Chest.Size.y);
	Rectangle rectKey = Rectangle(G.Key.Pos.x, G.Key.Pos.y, G.Key.Pos.x + G.Key.Size.x, G.Key.Pos.y + G.Key.Size.y);
	//herosCollision(G.rectMomie);
	//keyCollision();
	//chestCollision();
	for (int i = 0; i < 3; i++)
	{
		DeplacementMomies(G.MomieListe[i]);
	}
	collision(G.Heros);

}


void AssetsInit()
{
	// Size passé en ref et texture en param
	G.Heros.IdTex = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture);
	G.Heros.Size = G.Heros.Size * 2; // on peut zoomer la taille du sprite

	G.Key.IdTex = G2D::InitTextureFromString(G.Key.Size, G.Key.texture);
	G.Key.Size = G.Key.Size * 1.5; // on peut zoomer la taille du sprite

	G.Chest.IdTex = G2D::InitTextureFromString(G.Chest.Size, G.Chest.texture);
	G.Chest.Size = G.Chest.Size * 2.5; // on peut zoomer la taille du sprite

	for (int i = 0; i < 3; i = i + 1)
	{
		G.MomieListe[i].IdTex = G2D::InitTextureFromString(G.MomieListe[i].Size, G.MomieListe[i].texture);
		G.MomieListe[i].Size = G.MomieListe[i].Size * 2; // on peut zoomer la taille du sprite
	}
	

}

int main(int argc, char* argv[])
{
	G2D::InitWindow(argc, argv, V2(G.Lpix * 15, G.Lpix * 15), V2(200, 200), string("Labyrinthe"));

	AssetsInit();

	G2D::Run(Logic, render);

}


