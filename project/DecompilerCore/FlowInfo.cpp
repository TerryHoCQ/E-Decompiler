#include "FlowInfo.h"
#include <unordered_set>
#include "../dotGraph.h"
#include "../common.h"
#include "../Helper/CapstoneWrapper.h"

namespace DecompilerCore
{

	void FlowInfo::generateOps(Address startAddr)
	{
		addrlist.push_back(startAddr);
		fallthru();
	}

	void FlowInfo::generateBlocks(void)
	{
		collectEdges();
	}

	void FlowInfo::setRange(const Address& b, const Address& e)
	{
		baddr = b; 
		eaddr = e;
	}

	void FlowInfo::fallthru(void)
	{
		Address curaddr;

		while (true) {
			curaddr = addrlist.back();
			addrlist.pop_back();

			bool startbasic = true;
			if (!processInstruction(curaddr, startbasic)) {
				break;
			}
			if (addrlist.empty()) {
				break;
			}
		}
	}

	bool FlowInfo::processInstruction(Address& curaddr, bool& startbasic)
	{
		cs_insn* ins;

		while (true) {

			if (visitedAsm.count(curaddr)) {
				if (startbasic) {
					obank.findOp(curaddr)->opMarkStartBasic();
				}
				return true;
			}
			visitedAsm.insert(curaddr);

			AsmOp* currentAsm = obank.create(curaddr);
			if (!CapstoneWrapper::Instance().disasm(curaddr.getAddress(), ins)) {
				currentAsm->setOpcode(AsmOp::CPUI_ERROR);
				return true;
			}

			currentAsm->setAsmLen(ins->size);
			if (startbasic) {
				currentAsm->opMarkStartBasic();
				startbasic = false;
			}

			switch (ins->id)
			{
			case X86_INS_JAE:
			case X86_INS_JA:
			case X86_INS_JBE:
			case X86_INS_JB:
			case X86_INS_JCXZ:
			case X86_INS_JECXZ:
			case X86_INS_JE:
			case X86_INS_JGE:
			case X86_INS_JG:
			case X86_INS_JLE:
			case X86_INS_JL:
			case X86_INS_JNE:
			case X86_INS_JNO:
			case X86_INS_JNP:
			case X86_INS_JNS:
			case X86_INS_JO:
			case X86_INS_JP:
			case X86_INS_JRCXZ:
			case X86_INS_JS:
				currentAsm->setOpcode(AsmOp::CPUI_CBRANCH);
				currentAsm->opdata.JmpAddr = ins->detail->x86.operands[0].imm;
				addrlist.push_back(ins->detail->x86.operands[0].imm);
				addrlist.push_back(curaddr.getAddress() + ins->size);
				return true;
			case X86_INS_RET:
				currentAsm->setOpcode(AsmOp::CPUI_RETURN);
				return true;
			case X86_INS_JMP:
				return processJumpInstruction(ins, currentAsm);
			}
			curaddr = curaddr.getAddress() + ins->size;
		}

		return false;
	}

	bool FlowInfo::processJumpInstruction(cs_insn* ins, AsmOp* asmOp)
	{
		//无条件跳转
		if (ins->detail->x86.opcode[0] == 0xE9 || ins->detail->x86.opcode[0] == 0xEB) {
			asmOp->setOpcode(AsmOp::CPUI_BRANCH);
			addrlist.push_back(ins->detail->x86.operands[0].imm);
			asmOp->opdata.JmpAddr = ins->detail->x86.operands[0].imm;
			return true;
		}
		//switch case


		return false;;
	}

	void FlowInfo::collectEdges(void)
	{
		std::list<AsmOp*>::const_iterator iter = obank.beginDead();
		std::list<AsmOp*>::const_iterator iterend = obank.endDead();
		AsmOp* targ_op = 0;
		//下一条指令是否是新的basicBlock
		bool nextstart = false;
		while (iter != iterend) {

			AsmOp* op = *iter++;

			if (op->getSeqNum().getAddr().getAddress() == 0x0040105A) {
				int a = 0;
			}
			if (op->getSeqNum().getAddr().getAddress() == 0x00401090) {
				int a = 0;
			}

			if (iter == iterend) {
				nextstart = true;
			}
			else {
				nextstart = (*iter)->isBlockStart();
			}

			switch (op->getOpCode()) {

			case AsmOp::CPUI_BRANCH:
				targ_op = branchTarget(op);
				block_edge1.push_back(op);
				block_edge2.push_back(targ_op);
				break;
			case AsmOp::CPUI_BRANCHIND:
				//To do...
				break;
			case AsmOp::CPUI_RETURN:
				break;
			case AsmOp::CPUI_CBRANCH:
				targ_op = fallthruOp(op);
				block_edge1.push_back(op);
				block_edge2.push_back(targ_op);
				targ_op = branchTarget(op);
				block_edge1.push_back(op);
				block_edge2.push_back(targ_op);
				break;
			default:
				if (nextstart) {
					targ_op = fallthruOp(op);
					block_edge1.push_back(op);
					block_edge2.push_back(targ_op);
				}
				break;
			}
		}
	}

	DecompilerCore::AsmOp* FlowInfo::fallthruOp(AsmOp* op) const
	{
		Address nextAddress = op->getSeqNum().getAddr().getAddress() + op->getAsmLen();
		return obank.findOp(nextAddress);
	}

	DecompilerCore::AsmOp* FlowInfo::branchTarget(AsmOp* op) const
	{
		return obank.findOp(op->opdata.JmpAddr);
	}

	void showGraph()
	{
		//std::string result = "digraph CFGraph {\n";
		//for (std::map<Address, BasicBlock>::iterator it = basicBlocks.begin(); it != basicBlocks.end(); ++it) {
		//	std::string insLabel = "";
		//	for (unsigned int n = 0; n < it->second.insList.size(); ++n) {
		//		std::string diasmText = ZydisWrapper::Instance().GetDisasmText(it->second.insList[n].getOffset());
		//		if (diasmText != "") {
		//			insLabel = insLabel + diasmText + "\n";
		//		}
		//	}

		//	qstring labelStr;
		//	labelStr.sprnt("\t0x%X[fillcolor=%s,style=filled,shape=box,label=\"%s\" ]\n", it->second.startAddr, "lightblue", insLabel.c_str());
		//	result = result + std::string(labelStr.c_str(),labelStr.length());
		//}
		//result += "}";
		//FILE* hFile = qfopen("D:\\test.dot", "wb");
		//qfwrite(hFile, result.c_str(), result.length());
		//qfclose(hFile);
	}

}

