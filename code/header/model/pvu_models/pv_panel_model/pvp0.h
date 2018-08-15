#ifndef PVP0_H
#define PVP0_H

#include "header/model/pvu_models/pv_panel_model/pv_panel_model.h"
#include <cstdlib>

class PVP0 : public PV_PANEL_MODEL
{
    public:
        PVP0();
        PVP0(const PVP0& model);
        virtual ~PVP0();
        PVP0& operator=(const PVP0& model);
    public:
        virtual string get_model_name() const;

        virtual double get_double_data_with_index(size_t index) const;
        virtual double get_double_data_with_name(string par_name) const;
        virtual void set_double_data_with_index(size_t index, double value);
        virtual void set_double_data_with_name(string par_name, double value);

        virtual bool setup_model_with_steps_string(string data);
        virtual bool setup_model_with_psse_string(string data);
        virtual bool setup_model_with_bpa_string(string data);

        virtual void check();
        virtual void clear();
        virtual void report();
        virtual void save();
        virtual string get_standard_model_string() const;

        virtual size_t get_variable_index_from_variable_name(string var_name);
        virtual string get_variable_name_from_variable_index(size_t var_index);
        virtual double get_variable_with_index(size_t var_index);
        virtual double get_variable_with_name(string var_name);

        virtual string get_dynamic_data_in_psse_format() const;
        virtual string get_dynamic_data_in_bpa_format() const;
        virtual string get_dynamic_data_in_steps_format() const;
    private:
        void copy_from_const_model(const PVP0& model);
};

#endif // PVP0_H