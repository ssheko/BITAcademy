#pragma once
#include <windows.h>
#include <stdio.h>

class SpriteDIB
{
public:
public:
	enum
	{
		TYPE_BITMAP = 0x4d42
	};
	struct SPRITE
	{
		BYTE *byteImage;
		int	width;
		int height;
		int pitch;
	
		int centerPointX;
		int centerPointY;
	};
private:
protected:
	SPRITE *_spritePointer;
	int		_maxSprite;
	DWORD	_colorKey;
public:
	SpriteDIB(int maxSprite, DWORD colorKey);
	virtual ~SpriteDIB();

	bool LoadDIBSprite(int spriteIndex, const char *fileName, int centerPointX, int centerPointY);
	void ReleaseDIB(int spriteIndex);
	// �÷�Ű ó��
	void DrawSprite(int spriteIndex, int drawX, int drawY, BYTE *dest, int destWidth, int destHeight, int destPitch, int drawRate = 100);
	void DrawSpriteRed(int spriteIndex, int drawX, int drawY, BYTE *dest, int destWidth, int destHeight, int destPitch, int drawRate = 100);
	void DrawSpriteHalfAlpha(int spriteIndex, int drawX, int drawY, BYTE *dest, int destWidth, int destHeight, int destPitch, int drawRate = 100);
	// �÷�Ű ��ó��
	void DrawImage(int spriteIndex, int drawX, int drawY, BYTE *dest, int destWidth, int destHeight, int destPitch, int drawRate = 100);
};