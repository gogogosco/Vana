if questid == 3525 then -- Time Temple quest for memories
	if state == 0 then
		addQuest(3525);
		endQuest(3525);
		endQuest(3507);
		addText("Oh my gosh, you've grown so much since we first met! You've lost your memories? I'll take care of that.");
		sendOK();
		endNPC();
	end
else
	endNPC();
end