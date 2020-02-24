
/// <summary>Filter button handler for rpt viewer (FilterChangedEvent)</summary>
function OnFilterSettingChanged() {
    applyFilter("#main-frame");                     // apply filter both to the visible area of the report - ignore hidden cache 

    if ($("span.treeItemName.selected").parent().hasClass("filtered-out"))
        openSummary("main-summary");                // current page may be being filtered-out => switch to main summary

    updateCounts($("li#main-summary>ul>li:not(.filtered-out)"));

    addMainSummaryNote();
}

/// <summary>Adds a note about current filter setting to main summary</summary>
function addMainSummaryNote()
{
    var note = $("#filter-note-in-main-summary")[0];

    var filter = parseInt($("#main-frame").attr("filter-setting"));
    var str = " ";
    if (filter) {
        str = "Differences hidden by filter setting: ";

        if (filter & 0x4)
            str += "electrical constraints, ";
        if (filter & 0x8)
            str += "physical constraints, ";
        if (filter & 0x10)
            str += "spacing constraints, ";
        if (filter & 0x20)
            str += "same net spacing constraints, ";
        if (filter & 0x100)
            str += "properties, ";
        if (filter & 0x2)
            str += "structure, ";
    }

    note.textContent = str;
}

/// <summary>applies the filter setting to the <paramref name="scope"/></summary>
/// <param name="scope">jquery sub-string specifying the scope where to apply filters</param>
function applyFilter(scope) {
    var filterSetting = $("#main-frame").attr("filter-setting");
    if (filterSetting == null)
        return;                     // never set yet

    filterSetting = parseInt(filterSetting);

    scope += " ";
    // 1) reset previous
    var nodes = $(scope + ".filtered-out");
    nodes.removeClass("filtered-out");

    // 2) apply new filter
    nodes = $(scope + "[filter]");
    var len = nodes.length;
    for (var i = 0; i < len; i++) {
        var node = $(nodes[i]);
        var needFilter = parseInt(node.attr("filter"));
        if ((needFilter & filterSetting) == needFilter)
            node.addClass("filtered-out");
    }
}

/// <summary>Updates the child numbers in the tree for all the <paramref name="nodes"/></summary>
/// <param name="nodes">jqueried collection of nodes to update counts</param>
function updateCounts(nodes) {
    var childNumber = 0;
    var len = nodes.length;
    for (var i = 0; i < len; i++) {
        var node = nodes[i];
        var children = $("li#" + node.id + ">ul>li:not(.filtered-out)");
        if (children.length > 0) {
            var cn = updateCounts(children);

            var name = $("li#" + node.id + ">span.treeItemName")[0];
            var str = name.textContent;
            var ndx = str.indexOf('[');
            if (ndx == -1)                      // does not count chidren
            {
                childNumber++;
                continue;
            }
            str = str.substring(0, ndx + 1);  // trim the number from previous calculation

            childNumber += cn;
            str += cn.toString() + "]";
            name.textContent = str;
        }
        else
            childNumber++;
    }
    return (childNumber);
}
