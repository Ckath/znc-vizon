#include <znc/Client.h> /* I think these are the includes I need */
#include <znc/Chan.h>
#include <znc/Modules.h>

class CVIzon : public CModule {
public:
	MODCONSTRUCTOR(CVIzon) {
		bet.clear();
		topic_changed = 0;
	}

	virtual EModRet OnTopic(CNick& Nick, CChan& Channel, CString& sTopic) {
		/* use topic changes in #vizon as trigger for placing bets */
		if (!Channel.GetName().CaseCmp("#vizon")) {
			topic_changed = time(NULL);
		}
		return CONTINUE;
	}

	virtual void OnModCommand(const CString& sCommand) {
		CString sCmd = sCommand.Token(0);
		if (!sCmd.CaseCmp("check")) {
			PutModule("bet: " + (bet.empty() ? "random" : bet));
		} else if (!sCmd.CaseCmp("bet")) {
			if (sCommand.Token(1).empty()) {
				PutModule("specify bet");
				return;
			} if (!sCommand.Token(1).CaseCmp("random")) {
				bet.clear();
				PutModule("random bets will be used for future draws");
				return;
			}
			bet = sCommand.substr(sCommand.find(' ')+1);
			PutModule(bet + " will be used for future draws");
		}
	}

	virtual EModRet OnChanMsg(CNick& Nick, CChan& Channel, CString& sMessage) {
		/* yes, I'm using OnChanMsg as a scuffed timer, try and stop me */
		if (topic_changed && (time(NULL) - topic_changed) > 6969) {
			topic_changed = 0;
			if (!bet.empty()) { /* set bet */
				PutIRC("PRIVMSG vizon :bet " + bet);
				return CONTINUE;
			}

			/* random bet */
			int generated = 0;
			srand(time(NULL));
			while (generated < 6) {
				int b = (rand()%29)+1;
				CString bstr = " " + std::to_string(b) + " ";
				if (bet.find(bstr) == std::string::npos) {
					bet += generated ? std::to_string(b) + " " : bstr;
					generated++;
				}
			}
			PutIRC("PRIVMSG vizon :bet" + bet);
			bet.clear();
		}

        return CONTINUE;
    }


private:
	CString bet;
	time_t topic_changed;
};

MODULEDEFS(CVIzon, "module for automated #VIzon bets")
