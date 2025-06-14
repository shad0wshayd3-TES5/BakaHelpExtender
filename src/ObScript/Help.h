#pragma once

namespace ObScript::Help
{
	namespace FORM
	{
		namespace CELL
		{
			void Build();
		}

		void Print(const std::string_view& a_name, RE::FormType a_type);
	}

	namespace FUNC
	{
		void Print(const std::string_view& a_name);
	}

	namespace GLOB
	{
		void Print(const std::string_view& a_name);
	}

	namespace GMST
	{
		void Print(const std::string_view& a_name);
	}

	namespace HELP
	{
		void Print();
	}

	inline bool Execute(
		const RE::SCRIPT_PARAMETER*      a_paramInfo,
		RE::SCRIPT_FUNCTION::ScriptData* a_scriptData,
		RE::TESObjectREFR*               a_thisObj,
		RE::TESObjectREFR*               a_containingObj,
		RE::Script*                      a_scriptObj,
		RE::ScriptLocals*                a_locals,
		[[maybe_unused]] double&         a_result,
		std::uint32_t&                   a_opcodeOffsetPtr)
	{
		char a_name[512]{ '\0' };
		char a_type[512]{ '\0' };

		std::uint32_t a_code{ 0 };
		RE::Script::ParseParameters(
			a_paramInfo,
			a_scriptData,
			a_opcodeOffsetPtr,
			a_thisObj,
			a_containingObj,
			a_scriptObj,
			a_locals,
			a_name,
			&a_code,
			a_type);

		std::string_view name = a_name;
		const auto       type = RE::StringToFormType(a_type);

		if (name.empty())
		{
			HELP::Print();
			return true;
		}

		switch (a_code)
		{
		case 0:
			FUNC::Print(name);
			GMST::Print(name);
			GLOB::Print(name);
			FORM::Print(name, type);
			HELP::Print();
			break;
		case 1:
			FUNC::Print(name);
			HELP::Print();
			break;
		case 2:
			GMST::Print(name);
			HELP::Print();
			break;
		case 3:
			GLOB::Print(name);
			HELP::Print();
			break;
		case 4:
			FORM::Print(name, type);
			HELP::Print();
			break;
		default:
			HELP::Print();
			break;
		}

		return true;
	}

	inline void Install()
	{
		if (auto func = RE::SCRIPT_FUNCTION::LocateConsoleCommand("Help"sv))
		{
			static RE::SCRIPT_PARAMETER params[] = {
				{ "matchstring (optional)", RE::SCRIPT_PARAM_TYPE::kChar, true },
				{ "filter (optional)",      RE::SCRIPT_PARAM_TYPE::kInt,  true },
				{ "form type (optional)",   RE::SCRIPT_PARAM_TYPE::kChar, true }
			};

			func->SetParameters(params);
			func->executeFunction = &Execute;
		}
	}
}
