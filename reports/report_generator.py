from reportlab.platypus import (
    SimpleDocTemplate,
    Paragraph,
    Spacer
)

from reportlab.lib.styles import getSampleStyleSheet

import pandas as pd

def generate_pdf():

    df = pd.read_csv("data/energy_log.csv")

    pdf = SimpleDocTemplate(
        "reports/Energy_Report.pdf"
    )

    styles = getSampleStyleSheet()

    content = []

    content.append(
        Paragraph(
            "Smart Home Energy Monitoring Report",
            styles['Title']
        )
    )

    content.append(Spacer(1,12))

    latest = df.iloc[-1]

    content.append(
        Paragraph(
            f"Voltage: {latest['Voltage']} V",
            styles['Normal']
        )
    )

    content.append(
        Paragraph(
            f"Current: {latest['Current']} A",
            styles['Normal']
        )
    )

    content.append(
        Paragraph(
            f"Power: {latest['Power']} W",
            styles['Normal']
        )
    )

    content.append(
        Paragraph(
            f"Energy: {latest['Energy']} kWh",
            styles['Normal']
        )
    )

    content.append(
        Paragraph(
            f"Cost: ₹{latest['Cost']}",
            styles['Normal']
        )
    )

    pdf.build(content)

    print("PDF Report Created")