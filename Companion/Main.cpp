# include <Siv3D.hpp> // OpenSiv3D v0.6.5

#include "Companion.hpp"

void ShowCompanionTree(const Companion<String>& root, int32 level = 0)
{
	if (level > 0)
	{
		String s{ U"∟" };
		for (int32 i = 0; i < level - 1; ++i)s.push_front(U'　');

		Print << s << root.self();
	}
	else
	{
		Print << root.self();
	}

	auto children = root.getChildren();

	if (children.empty())
		return;

	for (auto& value : children)
	{
		ShowCompanionTree(*value, level + 1);
	}
}

void Main()
{
	String peoples[] = {U"Root",U"A" ,U"B" ,U"a1",U"a2",U"b1",U"b2" };

	Companion<String> root{ peoples[0] };
	Companion<String> A{ peoples[1] };
	Companion<String> B{ peoples[2] };
	Companion<String> A_a1{ peoples[3] };
	Companion<String> A_a2{ peoples[4] };
	Companion<String> B_b1{ peoples[5] };
	Companion<String> B_b2{ peoples[6] };

	A.join(root);
	B.join(root);
	A_a1.join(A);
	A_a2.join(A);
	B_b1.join(B);
	B_b2.join(B);

	while (System::Update())
	{
		ClearPrint();
		ShowCompanionTree(root);
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/tutorial/
//
// Tutorial
// https://siv3d.github.io/tutorial/tutorial/
//
// Siv3D コミュニティへの参加（Discord などで気軽に質問や交流, 最新情報の入手ができます）
// https://siv3d.github.io/ja-jp/community/community/
//
// Siv3D User Community
// https://siv3d.github.io/community/community/
//
// 新機能の提案やバグの報告 | Feedback
// https://siv3d.github.io/ja-jp/develop/report/
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
