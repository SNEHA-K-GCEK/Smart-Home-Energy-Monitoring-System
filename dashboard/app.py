import pandas as pd
import streamlit as st

st.title("Smart Home Energy Dashboard")

df = pd.read_csv("data/energy_log.csv")

st.dataframe(df)

st.line_chart(df["Power"])

st.line_chart(df["Energy"])

st.line_chart(df["Cost"])