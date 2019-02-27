#pragma once
#include	<windows.h>
#include	<d3dx9.h>
#ifndef DEBUG_TEXT
#define DEBUG_TEXT
//////////////////////////////////////////
//デバッグ用文字表示簡略化ツール
//////////////////////////////////////////
class Debug_text 
{
private:
	static const int text_max = 256;
	struct text_Box
	{
		D3DXVECTOR2 pos;
		DWORD color;
		char text[256];
		text_Box() {
			pos = D3DXVECTOR2(0, 0);
			color = 0;
			//memcpy(text, "",  text);
			ZeroMemory(text, sizeof(text));
		}
		void clear() {
			color = 0;
		}
	};

	text_Box text_box[text_max];

public:

	static Debug_text *getInstance()
	{
		static Debug_text instance;
		return &instance;
	}

	void Reset() {
		for (int i = 0; i < text_max; i++) {
			text_box[i].clear();
		}
	}
	void SetText(D3DXVECTOR2 pos ,DWORD color ,const char* format,...) {
		for (int i = 0; i < text_max; i++) {
			text_Box* b = &text_box[i];
			if (b->color != 0)continue;
			b->color = color;
			b->pos = pos;
			strcpy_s(b->text, 256, format);
			break;
		}
	}

	void Render() {
		for (int i = 0; i < text_max; i++) {
			if (text_box[i].color == 0)continue;
			{
				//テキスト描画
				///////////////////////////////////////
				///////////////////////////////////////
				///////////////////////////////////////
			}
		}
	}

private:


};
#endif //DEBUG_TEXT

#define pD_TEXT (Debug_text::getInstance())