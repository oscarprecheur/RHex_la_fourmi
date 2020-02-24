$(document).ready(function () { $(".viewSelector td").click(handlePerLyrDisplay); });

var PerLyrClsNames = { S: "showStat", D: "showDiff", A: "showAll" };

function handlePerLyrDisplay()
{
    var td = $(this).get(0);
    var clsName = td.className;
    var parent = td.parentNode.parentNode.parentNode.parentNode; 	// <parent>/table/tbody/tr/td - whoever has viewSelector
    if (parent.nodeName.toLowerCase() == "td")			// for one
        var target = $("#" + parent.id);
    else												// for all - parent.parentNode, because parent is div[filter] and we need its parent
        var target = $("#" + parent.parentNode.id + " .nonScalarDiff");


    for (cls in PerLyrClsNames)
    {
        if (cls == clsName)
            target.addClass(PerLyrClsNames[cls]);
        else
            target.removeClass(PerLyrClsNames[cls]);
    }

    return (false);
}
