#pragma once
#include "GhidraDecompiler.h"

class IDAArchitecture;

class EazyDecompiler:public GhidraDecompiler
{
public:
	explicit EazyDecompiler(std::unique_ptr<IDAArchitecture> architecture);
	~EazyDecompiler() = default;

	EazyDecompiler(const EazyDecompiler&) = delete;
	EazyDecompiler& operator=(const EazyDecompiler&) = delete;
	EazyDecompiler(EazyDecompiler&&) noexcept = default;
	EazyDecompiler& operator=(EazyDecompiler&&) = default;

	static std::unique_ptr<EazyDecompiler> build();
};