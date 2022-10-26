#pragma once
#include <Siv3D.hpp>

template<class ObjectT>
class Companion
{
public:

	Companion(ObjectT& _object)noexcept;

	~Companion();

	ObjectT& self()noexcept;

	const ObjectT& self()const noexcept;

	/// @brief 指定した親Companionに所属する
	void join(Companion& _parent);

	/// @brief 所属しているCompanionから離脱する
	void withdraw();

	/// @brief 親オブジェクトを取得する
	/// @return いない場合はnullptr
	Companion* getParent()const noexcept;

	/// @brief 最上位のCompanionを取得する
	/// @return 自分が最上位の場合はnullptr
	Companion* getRoot()const noexcept;

	/// @brief 子Companionをインデックスで取得する
	Companion* getChild(uint64 _index = 0ui64)const;

	/// @brief 子Companionを全て取得する
	Array<Companion*> getChildren()const noexcept;
 
	uint64 childCount()const noexcept;

private:

	ObjectT& m_self;

	Companion* m_parent{ nullptr };
	Companion* m_prev{ nullptr };
	Companion* m_next{ nullptr };
	Companion* m_children{ nullptr };

	uint64 m_childCount{ 0ui64 };

	void uncheckedGetChild(Companion*& _out, uint64 _index) const noexcept;

};

template<class ObjectT>
Companion<ObjectT>::Companion(ObjectT& _parent)noexcept
	: m_self(_parent) {}

template<class ObjectT>
Companion<ObjectT>::~Companion()
{
	//親から外れる
	withdraw();

	Companion* pChild = m_children;

	//全ての親子関係を断ち切る
	while (pChild)
	{
		pChild->withdraw();
		pChild = pChild->m_next;
	}
}

template<class ObjectT>
inline ObjectT& Companion<ObjectT>::self() noexcept
{
	return m_self;
}

template<class ObjectT>
inline const ObjectT& Companion<ObjectT>::self() const noexcept
{
	return m_self;
}

template<class ObjectT>
inline void Companion<ObjectT>::join(Companion& _parent)
{
	//既に同じ親に所属している
	if (m_parent == &_parent)
		return;

	//以前の親から離脱する
	withdraw();

	//既にいる親の子の手前に割り込む
	if (_parent.m_children)
	{
		_parent.m_children->m_next = this;
		m_prev = _parent.m_children;
	}
	//自身が最初の子
	else
	{
		_parent.m_children = this;
	}

	_parent.m_childCount += 1;

	m_parent = &_parent;
}

template<class ObjectT>
inline void Companion<ObjectT>::withdraw()
{
	//どこにも所属していない
	if (not m_parent)
		return;

	//自身が最後の子
	if ((not m_prev) and (not m_next))
	{
		m_parent->m_children = nullptr;
	}

	//先に所属した兄弟がいる
	if (m_prev)
	{
		m_prev->m_next = m_next;
	}

	//後に所属した兄弟がいる
	if (m_next)
	{
		m_next->m_prev = m_prev;
	}

	if (m_parent->m_childCount > 0)
	{
		m_parent->m_childCount -= 1;
	}

	m_parent = nullptr;
	m_next = nullptr;
	m_prev = nullptr;
}

template<class ObjectT>
inline Companion<ObjectT>* Companion<ObjectT>::getParent() const noexcept
{
	return m_parent;
}

template<class ObjectT>
inline Companion<ObjectT>* Companion<ObjectT>::getRoot() const noexcept
{
	//自分が最上位のオブジェクト
	if (not m_parent)
	{
		return nullptr;
	}

	Companion* pParent = m_parent;

	//親が最上位オブジェクト
	if (not pParent->m_parent)
	{
		return pParent;
	}

	//最上位のオブジェクトになるまでループ
	while (pParent->m_parent)
	{
		pParent = pParent->m_parent;
	}

	return pParent;
}

template<class ObjectT>
inline Companion<ObjectT>* Companion<ObjectT>::getChild(uint64 _index) const
{
	if (_index < m_childCount)
	{
		Companion* pChild = nullptr;
		uncheckedGetChild(pChild, _index);
		return pChild;
	}

	//範囲外指定
	throw std::out_of_range{"out of range: Companion::getChildren(uint64)"};
}

template<class ObjectT>
inline Array<Companion<ObjectT>*> Companion<ObjectT>::getChildren() const noexcept
{
	Array<Companion*> result{};

	//子がいない
	if (m_childCount == 0)
	{
		return result;
	}

	result.reserve(m_childCount);

	Companion* pChild = m_children;

	do
	{
		result << pChild;
	}
	while (pChild = pChild->m_next);

	return result;
}

template<class ObjectT>
inline uint64 Companion<ObjectT>::childCount() const noexcept
{
	return m_childCount;
}

template<class ObjectT>
inline void Companion<ObjectT>::uncheckedGetChild(Companion*& _out, uint64 _index) const noexcept
{
	Companion* pChild = m_children;

	uint64 index = 0ui64;

	while (pChild)
	{
		if (index == _index)
		{
			_out = pChild;
			break;
		}

		pChild = pChild->m_next;
		index += 1;
	}
}
