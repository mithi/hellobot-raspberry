def change_view2d(fig, relayout_data):
    if not relayout_data:
        return

    for axis in ["xaxis", "yaxis"]:
        for i in [0, 1]:
            key = f"{axis}.range[{i}]"
            if key not in relayout_data:
                continue

            fig["layout"][axis]["range"][i] = relayout_data[key]

    if "autosize" in relayout_data:
        fig["layout"]["autosize"] = True

    if "xaxis.autorange" in relayout_data:
        fig["layout"]["xaxis"]["autorange"] = True

    if "yaxis.autorange" in relayout_data:
        fig["layout"]["yaxis"]["autorange"] = True
