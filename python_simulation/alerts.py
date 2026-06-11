def check_alert(power):

    threshold = 2000

    if power > threshold:
        return "HIGH CONSUMPTION ALERT"

    return "Normal"