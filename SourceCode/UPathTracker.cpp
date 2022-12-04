//
// Created by Вячеслав Кривенко on 28.11.2022.
//

#include <Victoriam/Utils/UPathTracker.hpp>

VISRCBEG

namespace {

	String ConditionAppendSlash(const String &path) {
		if (path.at(path.size() - 1) == '/') return path;
		return path + '/';
	}

}

Path& Path::Instance() {
	static CPathTracker instance;
	return instance;
}

Path& Path::Mount(const StringView &actualPath) {
	auto& instance = Instance();
	instance.ActualToVirtual[actualPath] = {};
	instance.Temp = actualPath;
	return instance;
}

Path& Path::To(const StringView &virtualPath) {
	ActualToVirtual[Temp] = ConditionAppendSlash(virtualPath.data());
	VirtualToActual[ActualToVirtual[Temp]] = Temp;
	Temp = {};
	return *this;
}

String Path::Get(const StringView &virt) {
	auto& instance = Instance();
	if (Exists(virt))
		return instance.VirtualToActual.at(ConditionAppendSlash(virt.data()));
	return {};
}

CSet<StringView> Path::VirtualList() {
	auto instance = Instance();
	CSet<StringView> result = {};
	for (auto [virt, _] : instance.VirtualToActual) result.EmplaceBack(virt);
	return result;
}

CSet<StringView> Path::ActualList() {
	auto instance = Instance();
	CSet<StringView> result = {};
	for (auto [act, _] : instance.ActualToVirtual) result.EmplaceBack(act);
	return result;
}

Bool Path::Exists(const StringView &virt) {
	auto& instance = Instance();
	return instance.VirtualToActual.count(ConditionAppendSlash(virt.data()));
}

VISRCEND
