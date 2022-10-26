# Companion-with-Siv3D

## Reference

### T selef() noexcept
Companionが参照するオブジェクトを取得します

### void join(Companion<T>& _parent)
引数に指定したCompanionに所属します
親Companion側では子オブジェクトとして登録されます

### void withdraw()
所属しているCompanionから離脱します

### Companion<T>* getParent()const noexcept
親Companionを取得します
どこにも所属していない場合はnullptrが戻り値として返ります

### Companion<T>* getRoot()const noexcept
階層の最上位のCompanionを取得します
自身が最上位のオブジェクトの場合はnullptrが戻り値として返ります

### Companion<T>* getChild(uint64 _index = 0)const
配列の中から指定したインデックスに位置する子Companionを取得します

### Array<Companion<T>*> getChildren()const noexcept
自身の直下に属する子Companionを配列で取得します

### uint64 childCount()const noexcept
自身の直下に属する子Companionの数を取得します
